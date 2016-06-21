#include "World.hpp"
#include "../Server/Server.hpp"

World::World()
{
}

World::~World()
{
    // Free the memory.
    for(kantan::Entity* e : m_entities)
        delete e;

    for(kantan::DeletionMarkerComponent* dmc : m_deletionMarkerComponents)
        delete dmc;

    for(kantan::PolygonHitboxComponent* phc : m_polygonHitboxComponents)
        delete phc;

    for(kantan::MovementComponent* mc : m_movementComponents)
        delete mc;

    for(kantan::RotationComponent* rc : m_rotationComponents)
        delete rc;

    for(BasicStatsComponent* bsc : m_basicStatsComponents)
        delete bsc;

    for(ClientLinkComponent* clc : m_clientLinkComponents)
        delete clc;

    for(LevelStatsComponent* lsc : m_levelStatsComponents)
        delete lsc;

    for(NameComponent* nc : m_nameComponents)
        delete nc;

    for(StaticMarkerComponent* smc : m_staticMarkerComponents)
        delete smc;
}

void World::init()
{
    std::cout << "[WORLD] Map loading..." << std::endl;

    for(float x(0.f) ; x <= 1248.f ; x += 32.f)
        createBox(sf::Vector2f(x, 0.f));

    for(float y(32.f) ; y <= 768.f ; y += 32.f)
        createBox(sf::Vector2f(1248.f, y));

    for(float y(32.f) ; y <= 768.f ; y += 32.f)
        createBox(sf::Vector2f(0.f, y));

    for(float x(32.f) ; x <= 1248.f ; x += 32.f)
        createBox(sf::Vector2f(x, 768.f));

    std::cout << "[WORLD] Map loaded." << std::endl;
}

void World::update(sf::Time dt, Server* server)
{
    // Client inputs.
    m_clientInputSystem.update(m_clientLinkComponents, m_entities);

    // Rotations.
    //m_rotationSystem.update(dt, m_polygonHitboxComponents, m_rotationComponents);

    // Collision.
    m_collisionSystem.update(dt, m_polygonHitboxComponents, m_movementComponents);

    // Leveling up.
    m_levelUpSystem.update(m_levelStatsComponents, std::bind(&World::notifyLevelUp, this, std::placeholders::_1));

    // Clean the entities.
    cleanEntities(server);
}

void World::playerConnected(Client* client)
{
    createPlayer(sf::Vector2f(400.f, 600.f), client);
}

void World::playerDisconnected(Client* client)
{
    for(ClientLinkComponent* clc : m_clientLinkComponents)
    {
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
        }
    }
}

void World::sendUpdate(Client* client, sf::UdpSocket& socket)
{
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
            packet << ClientSide::EntityType::PLAYER;

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
                packet << ClientSide::PlayerStates::IDLE;
            else
                packet << ClientSide::PlayerStates::WALKING;

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
            packet << ClientSide::EntityType::NPC;

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
                packet << ClientSide::PlayerStates::IDLE;
            else
                packet << ClientSide::PlayerStates::WALKING;

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

void World::cleanEntities(Server* server)
{
    for(std::size_t i(0) ; i < m_deletionMarkerComponents.size() ;)
    {
        kantan::DeletionMarkerComponent* dmc = m_deletionMarkerComponents[i];

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

                    if(component->getName() == "DeletionMarker")
                        removeComponentFrom<kantan::DeletionMarkerComponent>(component, m_deletionMarkerComponents);
                    else if(component->getName() == "PolygonHitbox")
                        removeComponentFrom<kantan::PolygonHitboxComponent>(component, m_polygonHitboxComponents);
                    else if(component->getName() == "Movement")
                        removeComponentFrom<kantan::MovementComponent>(component, m_movementComponents);
                    else if(component->getName() == "Rotation")
                        removeComponentFrom<kantan::RotationComponent>(component, m_rotationComponents);
                    else if(component->getName() == "BasicStats")
                        removeComponentFrom<BasicStatsComponent>(component, m_basicStatsComponents);
                    else if(component->getName() == "ClientLink")
                        removeComponentFrom<ClientLinkComponent>(component, m_clientLinkComponents);
                    else if(component->getName() == "LevelStats")
                        removeComponentFrom<LevelStatsComponent>(component, m_levelStatsComponents);
                    else if(component->getName() == "NameComponent")
                        removeComponentFrom<NameComponent>(component, m_nameComponents);
                    else if(component->getName() == "StaticMarkerComponent")
                        removeComponentFrom<StaticMarkerComponent>(component, m_staticMarkerComponents);
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

    kantan::DeletionMarkerComponent* dmc = createDeletionMarkerComponent(e->getId());
    StaticMarkerComponent* smc = createStaticMarkerComponent(e->getId());

    smc->isStatic = isStatic;

    e->addComponent(dmc);
    e->addComponent(smc);

    m_entities.push_back(e);

    return e;
}

// createXXXComponent methods.
kantan::DeletionMarkerComponent* World::createDeletionMarkerComponent(std::size_t ownerId)
{
    kantan::DeletionMarkerComponent* dmc = new kantan::DeletionMarkerComponent(ownerId);
    m_deletionMarkerComponents.push_back(dmc);

    return dmc;
}

kantan::PolygonHitboxComponent* World::createPolygonHitboxComponent(std::size_t ownerId)
{
    kantan::PolygonHitboxComponent* phc = new kantan::PolygonHitboxComponent(ownerId);
    m_polygonHitboxComponents.push_back(phc);

    return phc;
}

kantan::MovementComponent* World::createMovementComponent(std::size_t ownerId)
{
    kantan::MovementComponent* mc = new kantan::MovementComponent(ownerId);
    m_movementComponents.push_back(mc);

    return mc;
}

kantan::RotationComponent* World::createRotationComponent(std::size_t ownerId)
{
    kantan::RotationComponent* rc = new kantan::RotationComponent(ownerId);
    m_rotationComponents.push_back(rc);

    return rc;
}

BasicStatsComponent* World::createBasicStatsComponent(std::size_t ownerId)
{
    BasicStatsComponent* bsc = new BasicStatsComponent(ownerId);
    m_basicStatsComponents.push_back(bsc);

    return bsc;
}

ClientLinkComponent* World::createClientLinkComponent(std::size_t ownerId)
{
    ClientLinkComponent* clc = new ClientLinkComponent(ownerId);
    m_clientLinkComponents.push_back(clc);

    return clc;
}

LevelStatsComponent* World::createLevelStatsComponent(std::size_t ownerId)
{
    LevelStatsComponent* lsc = new LevelStatsComponent(ownerId);
    m_levelStatsComponents.push_back(lsc);

    return lsc;
}

NameComponent* World::createNameComponent(std::size_t ownerId)
{
    NameComponent* nc = new NameComponent(ownerId);
    m_nameComponents.push_back(nc);

    return nc;
}

StaticMarkerComponent* World::createStaticMarkerComponent(std::size_t ownerId)
{
    StaticMarkerComponent* clc = new StaticMarkerComponent(ownerId);
    m_staticMarkerComponents.push_back(clc);

    return clc;
}

kantan::Entity* World::createPlayer(sf::Vector2f position, Client* client)
{
    // Create the entity.
    kantan::Entity* player = createEntity("Player");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createPolygonHitboxComponent(player->getId());
    kantan::MovementComponent* mc = createMovementComponent(player->getId());

    BasicStatsComponent* bsc = createBasicStatsComponent(player->getId());
    ClientLinkComponent* clc = createClientLinkComponent(player->getId());
    LevelStatsComponent* lsc = createLevelStatsComponent(player->getId());

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
    kantan::PolygonHitboxComponent* phc = createPolygonHitboxComponent(npc->getId());
    kantan::MovementComponent* mc = createMovementComponent(npc->getId());

    BasicStatsComponent* bsc = createBasicStatsComponent(npc->getId());
    NameComponent* nc = createNameComponent(npc->getId());

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
    kantan::Entity* box = createEntity("NPC", true);

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createPolygonHitboxComponent(box->getId());

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

// Notifies all the clients of the level up.
void World::notifyLevelUp(LevelStatsComponent* lsc)
{
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::LEVEL_UP << lsc->getOwnerId() << lsc->level;

    for(ClientLinkComponent* clc : m_clientLinkComponents)
    {
        if(clc->client != nullptr)
        {
            clc->client->gameTcp->send(packet);
        }
    }
}
