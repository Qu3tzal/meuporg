#include "World.hpp"
#include "../Server/Server.hpp"

int World::lastId = 0;

World::World()
    : m_id(lastId++)
    , m_worldTimeAccumulator(sf::Time::Zero)
    , m_serverTimeAccumulator(sf::Time::Zero)
{
}

World::~World()
{
    // Free the memory.
    for(kantan::Entity* e : m_entities)
        delete e;

    for(auto entry : m_components)
    {
        for(kantan::Component* c : entry.second)
            delete c;
    }
}

int World::getId() const
{
    return m_id;
}

void World::init(std::string mapFilepath)
{
    // Prepare physics.
    auto lambda = std::bind(&World::collisionResponsePredicate, this, std::placeholders::_1, std::placeholders::_2);
    m_collisionSystem.setCollisionResponsePredicate(lambda);

    // Init the spatial partitioning.
    m_collisionSystem.initSpatialPartitioning(sf::Vector2i(100, 100), 20.f, sf::Vector2f(0.f, 0.f));

    // Load map.
    Multithreading::outputMutex.lock();
    std::cout << "[WORLD|" << m_id << "] Map loading..." << std::endl;
    Multithreading::outputMutex.unlock();

    MapLoader mapLoader(mapFilepath, this);
    m_mapId = mapLoader.getMapId();

    Multithreading::outputMutex.lock();
    std::cout << "[WORLD|" << m_id << "] Map loaded in " << mapLoader.getLoadingTime().asMilliseconds() << " ms." << std::endl;
    Multithreading::outputMutex.unlock();
}

int World::getMapId() const
{
    return m_mapId;
}

void World::update(sf::Time dt, Server* server)
{
    //performancesCheck(dt);

    // Cooldowns.
    m_weaponCooldownSystem.update(dt, m_components["Weapon"]);

    // Client inputs.
    m_clientInputSystem.update(m_components["ClientLink"], m_entities, this);

    // AI.
    m_monsterAISystem.update(dt, m_components["MonsterAI"], m_components["Movement"], m_components["BasicStats"]);

    // Rotations.
    //m_rotationSystem.update(dt, m_components["PolygonHitbox"], m_components["Rotation"]);

    // Collision.
    m_collisionSystem.update(dt, m_components["PolygonHitbox"], m_components["Movement"]);
    checkCollisionEffects(m_collisionSystem.getCollisionRecord());

    // Leveling up.
    m_levelUpSystem.update(m_components["LevelStats"], std::bind(&World::notifyLevelUp, this, std::placeholders::_1));

    // Lifetime management.
    m_lifetimeSystem.update(dt, m_components["Lifetime"]);

    // Clean the entities.
    cleanEntities(server);
}

void World::playerConnected(Client* client, Server* server)
{
    PlayerData playerData = server->getPlayerData(client->username);

    createPlayer(sf::Vector2f(400.f, 600.f), client, playerData);

    // Log.
    Multithreading::outputMutex.lock();
    std::cout << "[WORLD|" << m_id << "] '" << client->username << "' joined (dbid: " << playerData.dbid << ")." << std::endl;
    Multithreading::outputMutex.unlock();
}

void World::playerDisconnected(Client* client, Server* server)
{
    for(kantan::Component* c : m_components["ClientLink"])
    {
        ClientLinkComponent* clc = static_cast<ClientLinkComponent*>(c);

        if(clc->client == client)
        {
            // Get the entity.
            kantan::Entity* entity = kantan::Entity::getEntityWithId(clc->getOwnerId(), m_entities);

            if(entity == nullptr)
                continue;

            // Mark as to delete.
            kantan::DeletionMarkerComponent* dmc = entity->getComponent<kantan::DeletionMarkerComponent>("DeletionMarker");
            dmc->marked = true;

            // Get the basic stats component and the level stats component.
            BasicStatsComponent* bsc = entity->getComponent<BasicStatsComponent>("BasicStats");
            LevelStatsComponent* lsc = entity->getComponent<LevelStatsComponent>("LevelStats");

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = entity->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Compute the left top corner.
            /// ! TODO: Check there is at least one point.
            sf::Vector2f leftTop(phc->points[0].x, phc->points[0].y);

            for(sf::Vector2f point : phc->points)
            {
                if(point.x < leftTop.x)
                    leftTop.x = point.x;

                if(point.y < leftTop.y)
                    leftTop.y = point.y;
            }

            // Save the data of the player.
            PlayerData playerData;

            playerData.dbid = clc->dbid;
            playerData.username = clc->client->username;

            playerData.worldId = m_id;
            playerData.positionX = leftTop.x;
            playerData.positionY = leftTop.y;

            playerData.hp = bsc->hp;
            playerData.maxhp = bsc->maxhp;
            playerData.strength = bsc->strength;
            playerData.agility = bsc->agility;
            playerData.resistance = bsc->resistance;

            playerData.xp = lsc->xp;
            playerData.level = lsc->level;

            server->writePlayerData(playerData);

            // Null the client link.
            clc->client = nullptr;

            // Log.
            Multithreading::outputMutex.lock();
            std::cout << "[WORLD|" << m_id << "] '" << client->username << "' left." << std::endl;
            Multithreading::outputMutex.unlock();
        }
    }
}

void World::sendUpdate(Client* client, sf::UdpSocket& socket)
{
    // Check the client belongs to our world.
    if(client->currentWorld != m_id)
        return;

    unsigned long long packetId = client->lastPacketIdSent;

    for(kantan::Entity* e : m_entities)
    {
        // Check if the entity is marked as static.
        StaticMarkerComponent* smc = e->getComponent<StaticMarkerComponent>("StaticMarker");

        // If static, do not send updates to client.
        if(smc->isStatic)
            continue;

        packetId++;

        sf::Packet packet;
        packet << NetworkValues::UPDATE << packetId << m_id << e->getId();

        if(e->getName() == "Player")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::ENTITYTYPE_PLAYER;

            // Get the CLC.
            ClientLinkComponent* clc = e->getComponent<ClientLinkComponent>("ClientLink");

            if(clc == nullptr || clc->client == nullptr)
                continue;

            packet << clc->client->username;

            // Get the movement component.
            kantan::MovementComponent* mc = e->getComponent<kantan::MovementComponent>("Movement");

            if(mc == nullptr)
                continue;

            // Get the basic stats component.
            BasicStatsComponent* bsc = e->getComponent<BasicStatsComponent>("BasicStats");

            // Set the state.
            if(bsc != nullptr && bsc->isDead)
            {
                packet << ClientSide::PlayerStates::PLAYERSTATE_DEAD;
            }
            else
            {
                if(mc->velocity == sf::Vector2f(0.f, 0.f))
                    packet << ClientSide::PlayerStates::PLAYERSTATE_IDLE;
                else
                    packet << ClientSide::PlayerStates::PLAYERSTATE_WALKING;
            }

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Set the position.
            packet << getLeftTop(phc->points);

            // Set the velocity.
            packet << mc->velocity;

            // Check component.
            if(bsc == nullptr)
                continue;

            // Set the stats.
            packet << bsc->hp << bsc->maxhp << bsc->strength << bsc->agility << bsc->resistance;

            // Get the level stats component.
            LevelStatsComponent* lsc = e->getComponent<LevelStatsComponent>("LevelStats");

            if(lsc == nullptr)
                continue;

            // Set the stats.
            packet << lsc->xp << lsc->level;
        }
        else if(e->getName() == "NPC")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::ENTITYTYPE_NPC;

            // Get the name.
            NameComponent* nc = e->getComponent<NameComponent>("Name");

            if(nc == nullptr)
                continue;

            packet << nc->name;

            // Get the movement component.
            kantan::MovementComponent* mc = e->getComponent<kantan::MovementComponent>("Movement");

            if(mc == nullptr)
                continue;

            // Set the state.
            if(mc->velocity == sf::Vector2f(0.f, 0.f))
                packet << ClientSide::NPCStates::NPCSTATE_IDLE;
            else
                packet << ClientSide::NPCStates::NPCSTATE_WALKING;

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Set the position.
            packet << getLeftTop(phc->points);

            // Set the velocity.
            packet << mc->velocity;

            // Set the NPC's id.
            packet << nc->id;
        }
        else if(e->getName() == "Monster")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::ENTITYTYPE_MONSTER;

            packet << "Monster";

            // Get the movement component.
            kantan::MovementComponent* mc = e->getComponent<kantan::MovementComponent>("Movement");

            if(mc == nullptr)
                continue;

            // Get the basic stats component.
            BasicStatsComponent* bsc = e->getComponent<BasicStatsComponent>("BasicStats");

            // Set the state.
            if(bsc != nullptr && bsc->isDead)
            {
                packet << ClientSide::MonsterStates::MONSTERSTATE_DEAD;
            }
            else
            {
                if(mc->velocity == sf::Vector2f(0.f, 0.f))
                    packet << ClientSide::MonsterStates::MONSTERSTATE_IDLE;
                else
                    packet << ClientSide::MonsterStates::MONSTERSTATE_WALKING;
            }

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Set the position.
            packet << getLeftTop(phc->points);

            // Set the velocity.
            packet << mc->velocity;
        }
        else if(e->getName() == "Bullet")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::ENTITYTYPE_BULLET;
            packet << "Bullet" << 0; // Default name and state.

            // Get the movement component.
            kantan::MovementComponent* mc = e->getComponent<kantan::MovementComponent>("Movement");

            if(mc == nullptr)
                continue;

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Set the position.
            packet << getLeftTop(phc->points);

            // Set the velocity.
            packet << mc->velocity;

            // Get the damage component.
            DamageComponent* dc = e->getComponent<DamageComponent>("Damage");

            if(dc == nullptr)
                continue;

            // Set the emitter id.
            packet << dc->emitter;
        }
        else if(e->getName() == "Tower")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::ENTITYTYPE_TOWER;
            packet << "Tower" << 0; // Default name and state.

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(phc == nullptr)
                continue;

            // Set the position.
            packet << getLeftTop(phc->points);

            // Set the velocity.
            packet << sf::Vector2f(0.f, 0.f);

            // Get the basic stats component.
            BasicStatsComponent* bsc = e->getComponent<BasicStatsComponent>("BasicStats");

            // Check component.
            if(bsc == nullptr)
                continue;

            // Set the stats.
            packet << bsc->hp << bsc->maxhp << bsc->strength << bsc->agility << bsc->resistance;
        }

        // Send the packet.
        socket.send(packet, client->ip, client->udpPort);
    }

    // Update the last packet id sent.
    client->lastPacketIdSent = packetId;
}

void World::giveXpTo(std::string username, float amount)
{
    if(amount <= 0.f)
        return;

    // Check the player exists.
    for(kantan::Component* component : m_components["ClientLink"])
    {
        ClientLinkComponent* clc = static_cast<ClientLinkComponent*>(component);

        // Check the username.
        if(clc->client->username != username)
            continue;

        // Retrieve the entity.
        kantan::Entity* entity = kantan::Entity::getEntityWithId(clc->getOwnerId(), m_entities);

        if(entity == nullptr)
            continue;

        // Get the XP component.
        LevelStatsComponent* lsc = entity->getComponent<LevelStatsComponent>("LevelStats");

        if(lsc == nullptr)
            continue;

        // Give the XP.
        lsc->xp += amount;

        // Log.
        Multithreading::outputMutex.lock();
        std::cout << "[WORLD|" << m_id << "] " << username << " got " << amount << " XP." << std::endl;
        Multithreading::outputMutex.unlock();
    }
}

void World::onRespawn(Client* client, std::size_t spawnId)
{
    for(kantan::Component* component : m_components["ClientLink"])
    {
        ClientLinkComponent* clc = component->convert<ClientLinkComponent>();

        if(clc == nullptr || clc->client != client)
            continue;

        return respawn(clc->getOwnerId());
    }
}

kantan::Entity* World::getEntity(const std::size_t& id)
{
    auto itr = std::find_if(m_entities.begin(), m_entities.end(), [&](kantan::Entity* e){
                        return e->getId() == id;
                 });

    if(itr == m_entities.end())
        return nullptr;

    return (*itr);
}

void World::performancesCheck(sf::Time serverdt)
{
    m_worldTimeAccumulator += m_worldClock.restart();
    m_serverTimeAccumulator += serverdt;

    if(m_serverTimeAccumulator >= sf::seconds(1.f))
    {
        sf::Time diff = m_worldTimeAccumulator - m_serverTimeAccumulator;

        if(diff > sf::Time::Zero)
        {
            Multithreading::outputMutex.lock();
            std::cout << "[WORLD|" << m_id << "] is " << diff.asMilliseconds() << "ms in advance." << std::endl;
            std::cout << "\tworld time: " << m_worldTimeAccumulator.asMilliseconds() << std::endl;
            std::cout << "\tserver time: " << m_serverTimeAccumulator.asMilliseconds() << std::endl;
            Multithreading::outputMutex.unlock();
        }
        else if(diff < sf::Time::Zero)
        {
            Multithreading::outputMutex.lock();
            std::cout << "[WORLD|" << m_id << "] is " << -diff.asMilliseconds() << "ms late." << std::endl;
            std::cout << "\tworld time: " << m_worldTimeAccumulator.asMilliseconds() << std::endl;
            std::cout << "\tserver time: " << m_serverTimeAccumulator.asMilliseconds() << std::endl;
            Multithreading::outputMutex.unlock();
        }
        else
        {
            Multithreading::outputMutex.lock();
            std::cout << "[WORLD|" << m_id << "] is perfectly synced !" << std::endl;
            Multithreading::outputMutex.unlock();
        }

        m_worldTimeAccumulator = sf::Time::Zero;
        m_serverTimeAccumulator = sf::Time::Zero;
    }
}

void World::cleanEntities(Server* server)
{
    for(std::size_t i(0) ; i < m_components["DeletionMarker"].size() ;)
    {
        kantan::Component* c = m_components["DeletionMarker"][i];
        kantan::DeletionMarkerComponent* dmc = static_cast<kantan::DeletionMarkerComponent*>(c);

        if(dmc->marked)
        {
            auto itr = std::find_if(m_entities.begin(), m_entities.end(), [dmc](kantan::Entity* e){
                            return dmc->getOwnerId() == e->getId();
                        });

            if(itr != m_entities.end())
            {
                kantan::Entity* entity = (*itr);
                std::unordered_map<std::string, kantan::Component*> components = entity->getAllComponents();

                for(std::pair<std::string, kantan::Component*> componentPair : components)
                {
                    kantan::Component* component = componentPair.second;

                    removeComponentFrom(component, m_components[component->getName()]);
                }

                m_entities.erase(itr);

                // Notify the entity has been removed.
                server->notifyEntityRemoved(entity->getId());
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
}

kantan::Entity* World::createEntity(std::string name, bool isStatic)
{
    kantan::Entity* e = new kantan::Entity(name);

    kantan::DeletionMarkerComponent* dmc = createComponent<kantan::DeletionMarkerComponent>(e->getId());
    StaticMarkerComponent* smc = createComponent<StaticMarkerComponent>(e->getId());

    smc->isStatic = isStatic;

    e->addComponent(dmc);
    e->addComponent(smc);

    m_entities.push_back(e);

    return e;
}

// createXXX methods.
kantan::Entity* World::createPlayer(sf::Vector2f position, Client* client, const PlayerData& playerData)
{
    // Create the entity.
    kantan::Entity* player = createEntity("Player");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(player->getId());
    kantan::MovementComponent* mc = createComponent<kantan::MovementComponent>(player->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(player->getId());
    ClientLinkComponent* clc = createComponent<ClientLinkComponent>(player->getId());
    LevelStatsComponent* lsc = createComponent<LevelStatsComponent>(player->getId());
    WeaponComponent* wc = createComponent<WeaponComponent>(player->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(31.f, 0.f),
            position + sf::Vector2f(31.f, 48.f),
            position + sf::Vector2f(0.f, 48.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = 100.f;

    clc->client = client;
    clc->dbid = playerData.dbid;

    bsc->hp = playerData.hp;
    bsc->maxhp = playerData.maxhp;
    bsc->strength = playerData.strength;
    bsc->agility = playerData.agility;
    bsc->resistance = playerData.resistance;

    lsc->xp = playerData.xp;
    lsc->level = playerData.level;

    wc->name = "Super ultra gun";
    wc->baseDamage = 25.f;
    wc->cooldown = sf::seconds(0.2f);
    wc->projectileSpeed = 1000.f;
    wc->projectileLifetime = sf::seconds(0.5f);

    // Add the components to the entity.
    player->addComponent(phc);
    player->addComponent(mc);
    player->addComponent(bsc);
    player->addComponent(clc);
    player->addComponent(lsc);
    player->addComponent(wc);

    // Return the entity.
    return player;
}

kantan::Entity* World::createNPC(sf::Vector2f position)
{
    // Create the entity.
    kantan::Entity* npc = createEntity("NPC");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(npc->getId());
    kantan::MovementComponent* mc = createComponent<kantan::MovementComponent>(npc->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(npc->getId());
    NameComponent* nc = createComponent<NameComponent>(npc->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(31.f, 0.f),
            position + sf::Vector2f(31.f, 48.f),
            position + sf::Vector2f(0.f, 48.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = 100.f;

    nc->id = 0;
    nc->name = "Random NPC";

    // Add the components to the entity.
    npc->addComponent(phc);
    npc->addComponent(mc);
    npc->addComponent(bsc);
    npc->addComponent(nc);

    // Return the entity.
    return npc;
}

kantan::Entity* World::createBox(sf::Vector2f position)
{
    // Create the entity.
    kantan::Entity* box = createEntity("Box", true);

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(box->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(32.f, 0.f),
            position + sf::Vector2f(32.f, 32.f),
            position + sf::Vector2f(0.f, 32.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    // Add the components to the entity.
    box->addComponent(phc);

    // Return the entity.
    return box;
}

kantan::Entity* World::createMonster(sf::Vector2f position)
{
    // Create the entity.
    kantan::Entity* monster = createEntity("Monster");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(monster->getId());
    kantan::MovementComponent* mc = createComponent<kantan::MovementComponent>(monster->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(monster->getId());
    MonsterAIComponent* maic = createComponent<MonsterAIComponent>(monster->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(31.f, 0.f),
            position + sf::Vector2f(31.f, 48.f),
            position + sf::Vector2f(0.f, 48.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = 100.f;

    // Add the components to the entity.
    monster->addComponent(phc);
    monster->addComponent(mc);
    monster->addComponent(bsc);
    monster->addComponent(maic);

    // Return the entity.
    return monster;
}

kantan::Entity* World::createBullet(sf::Vector2f position, std::size_t emitter, sf::Vector2f direction, float maxSpeed, float damage, sf::Time projectileLifetime)
{
    // Create the entity.
    kantan::Entity* bullet = createEntity("Bullet");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(bullet->getId());
    kantan::MovementComponent* mc = createComponent<kantan::MovementComponent>(bullet->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(bullet->getId());
    DamageComponent* dc = createComponent<DamageComponent>(bullet->getId());
    LifetimeComponent* lc = createComponent<LifetimeComponent>(bullet->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(8.f, 0.f),
            position + sf::Vector2f(8.f, 8.f),
            position + sf::Vector2f(0.f, 8.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = maxSpeed;
    mc->velocity = kantan::normalize(direction) * mc->maximumSpeed;

    dc->emitter = emitter;
    dc->damage = damage;

    lc->maxlifetime = projectileLifetime;
    lc->callback = [&](std::size_t entityId){
            // Find the entity.
            auto itr = std::find_if(m_entities.begin(), m_entities.end(), [&](kantan::Entity* e) -> bool {
                                        return e->getId() == entityId;
                                    });

            if(itr != m_entities.end())
            {
                // Mark it as to delete.
                kantan::DeletionMarkerComponent* dmc = (*itr)->getComponent<kantan::DeletionMarkerComponent>("DeletionMarker");
                dmc->marked = true;
            }
        };

    // Add the components to the entity.
    bullet->addComponent(phc);
    bullet->addComponent(mc);
    bullet->addComponent(bsc);
    bullet->addComponent(dc);
    bullet->addComponent(lc);

    // Return the entity.
    return bullet;
}

kantan::Entity* World::createTower(sf::Vector2f position)
{
    // Create the entity.
    kantan::Entity* tower = createEntity("Tower");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(tower->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(tower->getId());
    TowerAIComponent* taic = createComponent<TowerAIComponent>(tower->getId());
    WeaponComponent* wc = createComponent<WeaponComponent>(tower->getId());

    // Configure the components.
    phc->points = {
            position + sf::Vector2f(0.f, 0.f),
            position + sf::Vector2f(48.f, 0.f),
            position + sf::Vector2f(48.f, 107.f),
            position + sf::Vector2f(0.f, 107.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    bsc->hp = 500.f;
    bsc->maxhp = 500.f;
    bsc->strength = 0.f;
    bsc->agility = 0.f;
    bsc->resistance = 0.f;

    wc->name = "Super ultra tower gun";
    wc->baseDamage = 25.f;
    wc->cooldown = sf::seconds(0.5f);
    wc->projectileSpeed = 1000.f;
    wc->projectileLifetime = sf::seconds(0.5f);

    // Add the components to the entity.
    tower->addComponent(phc);
    tower->addComponent(bsc);
    tower->addComponent(taic);
    tower->addComponent(wc);

    // Return the entity.
    return tower;
}

// Notifies all the clients of the level up.
void World::notifyLevelUp(LevelStatsComponent* lsc)
{
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::LEVEL_UP << lsc->getOwnerId() << lsc->level;

    for(kantan::Component* c : m_components["ClientLink"])
    {
        ClientLinkComponent* clc = static_cast<ClientLinkComponent*>(c);

        if(clc->client != nullptr)
        {
            clc->client->gameTcp->send(packet);
        }
    }
}

// Notifies all the clients of the kill.
void World::notifyKill(std::size_t killerId, std::size_t killedId)
{
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::KILL << killerId << killedId;

    Multithreading::outputMutex.lock();
    std::cout << "[WORLD|" << m_id << "] Entity #" << killerId << " killed entity #" << killedId << "." << std::endl;
    Multithreading::outputMutex.unlock();

    for(kantan::Component* c : m_components["ClientLink"])
    {
        ClientLinkComponent* clc = static_cast<ClientLinkComponent*>(c);

        if(clc->client != nullptr)
        {
            clc->client->gameTcp->send(packet);
        }
    }
}

// Predicate for the physics engine.
bool World::collisionResponsePredicate(const std::size_t& firstEntityId, const std::size_t& secondEntityId)
{
    // Get the entities.
    kantan::Entity* firstEntity = getEntity(firstEntityId);
    kantan::Entity* secondEntity = getEntity(secondEntityId);

    // If one of the entities does not exist, we do not collide.
    if(firstEntity == nullptr || secondEntity == nullptr)
        return false;

    // Check the type of the entities.
    if(firstEntity->getName() == "Bullet")
    {
        // Check the other entity is not the emitter.
        DamageComponent* dc = firstEntity->getComponent<DamageComponent>("Damage");

        if(dc != nullptr)
            if(dc->emitter != -1 && (std::size_t)(dc->emitter) == secondEntityId)
                return false;
    }
    else if(secondEntity->getName() == "Bullet")
    {
        // Check the other entity is not the emitter.
        DamageComponent* dc = secondEntity->getComponent<DamageComponent>("Damage");

        if(dc != nullptr)
            if(dc->emitter != -1 && (std::size_t)(dc->emitter) == firstEntityId)
                return false;
    }

    // Collide otherwise.
    return true;
}

void World::checkCollisionEffects(const std::vector<std::tuple<std::size_t, std::size_t, sf::Vector2f>>& collisionRecord)
{
    for(const std::tuple<std::size_t, std::size_t, sf::Vector2f>& collisionPair : collisionRecord)
    {
        // Get the entities.
        kantan::Entity* firstEntity = getEntity(std::get<0>(collisionPair));
        kantan::Entity* secondEntity = getEntity(std::get<1>(collisionPair));

        // If one of the entities does not exist, we do not collide.
        if(firstEntity == nullptr || secondEntity == nullptr)
            continue;

        if(firstEntity->getName() == "Bullet" && secondEntity->getName() == "Bullet")
        {
            kantan::DeletionMarkerComponent* dmc_first = firstEntity->getComponent<kantan::DeletionMarkerComponent>("DeletionMarker");
            kantan::DeletionMarkerComponent* dmc_second = secondEntity->getComponent<kantan::DeletionMarkerComponent>("DeletionMarker");

            if(dmc_first != nullptr)
                dmc_first->marked = true;

            if(dmc_second != nullptr)
                dmc_second->marked = true;
        }
        else if(firstEntity->getName() == "Bullet" || secondEntity->getName() == "Bullet")
        {
            kantan::Entity *target, *bullet;

            if(firstEntity->getName() == "Bullet")
            {
                target = secondEntity;
                bullet = firstEntity;
            }
            else
            {
                target = firstEntity;
                bullet = secondEntity;
            }

            // Check the other entity is not the emitter.
            DamageComponent* dc = bullet->getComponent<DamageComponent>("Damage");

            if(dc == nullptr)
                continue;

            if(dc->emitter != -1 && (std::size_t)(dc->emitter) == target->getId())
                continue;

            // Deal damages to the target.
            BasicStatsComponent* bscTarget = target->getComponent<BasicStatsComponent>("BasicStats");

            if(bscTarget != nullptr && !bscTarget->isDead)
            {
                bscTarget->hp -= std::max(dc->damage - bscTarget->resistance, 0.f);

                if(bscTarget->hp <= 0.f)
                {
                    bscTarget->hp = 0.f;

                    onKill(dc->emitter, bscTarget->getOwnerId());
                    notifyKill(dc->emitter, bscTarget->getOwnerId());
                }

                // Destroy the bullet.
                kantan::DeletionMarkerComponent* dmcBullet = bullet->getComponent<kantan::DeletionMarkerComponent>("DeletionMarker");

                if(dmcBullet != nullptr)
                    dmcBullet->marked = true;
            }
        }
    }
}

// Manages the effect of a death.
void World::onKill(std::size_t killerId, std::size_t killedId)
{
    kantan::Entity* killedEntity = getEntity(killedId);

    // Deactivate hitbox.
    kantan::PolygonHitboxComponent* phc = killedEntity->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

    if(phc != nullptr)
        phc->isBlocking = false;

    // Set dead state.
    BasicStatsComponent* bsc = killedEntity->getComponent<BasicStatsComponent>("BasicStats");

    if(bsc != nullptr)
        bsc->isDead = true;

    // Give XP for the kill.
    kantan::Entity* killerEntity = getEntity(killerId);

    LevelStatsComponent* lsc = killerEntity->getComponent<LevelStatsComponent>("LevelStats");

    if(lsc != nullptr)
        lsc->xp += 10.f;
}

void World::addSpawnPoint(sf::Vector2f spawn)
{
    m_spawns.push_back(spawn);
}

void World::respawn(std::size_t entityId, std::size_t spawnId)
{
    kantan::Entity* entity = getEntity(entityId);

    if(entity == nullptr)
        return;

    // Reactivate hitbox.
    kantan::PolygonHitboxComponent* phc = entity->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

    if(phc != nullptr)
    {
        phc->isBlocking = true;

        // Translate to position.
        sf::Transform transform(sf::Transform::Identity);
        transform.translate(m_spawns[spawnId] - kantan::getCenter(phc->points));

        for(sf::Vector2f& point : phc->points)
            point = transform.transformPoint(point);
    }

    // Set alive state and restore hp.
    BasicStatsComponent* bsc = entity->getComponent<BasicStatsComponent>("BasicStats");

    if(bsc != nullptr)
    {
        bsc->isDead = false;
        bsc->hp = bsc->maxhp;
    }
}
