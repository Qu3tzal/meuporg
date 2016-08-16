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

    // Client inputs.
    m_clientInputSystem.update(m_components["ClientLink"], m_entities);

    // Rotations.
    //m_rotationSystem.update(dt, m_components["PolygonHitbox"], m_components["Rotation"]);

    // Collision.
    m_collisionSystem.update(dt, m_components["PolygonHitbox"], m_components["Movement"]);

    // Leveling up.
    m_levelUpSystem.update(m_components["LevelStats"], std::bind(&World::notifyLevelUp, this, std::placeholders::_1));

    // Clean the entities.
    cleanEntities(server);
}

void World::playerConnected(Client* client)
{
    createPlayer(sf::Vector2f(400.f, 600.f), client);

    // Log.
    Multithreading::outputMutex.lock();
    std::cout << "[WORLD|" << m_id << "] '" << client->username << "' joined." << std::endl;
    Multithreading::outputMutex.unlock();
}

void World::playerDisconnected(Client* client)
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
        packet << NetworkValues::UPDATE << packetId << e->getId();

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

            // Set the state.
            if(mc->velocity == sf::Vector2f(0.f, 0.f))
                packet << ClientSide::PlayerStates::PLAYERSTATE_IDLE;
            else
                packet << ClientSide::PlayerStates::PLAYERSTATE_WALKING;

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

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

            // Set the position.
            packet << leftTop;

            // Set the velocity.
            packet << mc->velocity;

            // Get the basic stats component.
            BasicStatsComponent* bsc = e->getComponent<BasicStatsComponent>("BasicStats");

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

            // Set the position.
            packet << leftTop;

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

            // Set the state.
            if(mc->velocity == sf::Vector2f(0.f, 0.f))
                packet << ClientSide::MonsterStates::MONSTERSTATE_IDLE;
            else
                packet << ClientSide::MonsterStates::MONSTERSTATE_IDLE;

            // Get the polygon hitbox component.
            kantan::PolygonHitboxComponent* phc = e->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

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

            // Set the position.
            packet << leftTop;

            // Set the velocity.
            packet << mc->velocity;
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
kantan::Entity* World::createPlayer(sf::Vector2f position, Client* client)
{
    // Create the entity.
    kantan::Entity* player = createEntity("Player");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createComponent<kantan::PolygonHitboxComponent>(player->getId());
    kantan::MovementComponent* mc = createComponent<kantan::MovementComponent>(player->getId());

    BasicStatsComponent* bsc = createComponent<BasicStatsComponent>(player->getId());
    ClientLinkComponent* clc = createComponent<ClientLinkComponent>(player->getId());
    LevelStatsComponent* lsc = createComponent<LevelStatsComponent>(player->getId());

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

    // Add the components to the entity.
    player->addComponent(phc);
    player->addComponent(mc);
    player->addComponent(bsc);
    player->addComponent(clc);
    player->addComponent(lsc);

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

    // Return the entity.
    return monster;
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
