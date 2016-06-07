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

    for(ClientLinkComponent* clc : m_clientLinkComponents)
        delete clc;
}

void World::init()
{

}

void World::update(sf::Time dt, Server* server)
{
    // Client inputs.
    m_clientInputSystem.update(m_clientLinkComponents, m_entities);

    // Rotations.
    //m_rotationSystem.update(dt, m_polygonHitboxComponents, m_rotationComponents);

    // Collision.
    m_collisionSystem.update(dt, m_polygonHitboxComponents, m_movementComponents);

    // Clean the entities.
    cleanEntities(server);
}

void World::playerConnected(Client* client)
{
    createPlayer(client);
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
        }
        else if(e->getName() == "NPC")
        {
            // Set the entity type.
            packet << ClientSide::EntityType::NPC;
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
                    else if(component->getName() == "ClientLink")
                        removeComponentFrom<ClientLinkComponent>(component, m_clientLinkComponents);
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

kantan::Entity* World::createEntity(std::string name)
{
    kantan::Entity* e = new kantan::Entity(name);

    kantan::DeletionMarkerComponent* dmc = createDeletionMarkerComponent(e->getId());
    e->addComponent(dmc);

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

ClientLinkComponent* World::createClientLinkComponent(std::size_t ownerId)
{
    ClientLinkComponent* clc = new ClientLinkComponent(ownerId);
    m_clientLinkComponents.push_back(clc);

    return clc;
}

kantan::Entity* World::createPlayer(Client* client)
{
    // Create the entity.
    kantan::Entity* player = createEntity("Player");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createPolygonHitboxComponent(player->getId());
    kantan::MovementComponent* mc = createMovementComponent(player->getId());
    ClientLinkComponent* clc = createClientLinkComponent(player->getId());

    // Configure the components.
    phc->points = {
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(31.f, 0.f),
            sf::Vector2f(31.f, 48.f),
            sf::Vector2f(0.f, 48.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = 1000.f;

    clc->client = client;

    // Add the components to the entity.
    player->addComponent(phc);
    player->addComponent(mc);
    player->addComponent(clc);

    // Return the entity.
    return player;
}

kantan::Entity* World::createNPC()
{
    // Create the entity.
    kantan::Entity* npc = createEntity("NPC");

    // Create the components.
    kantan::PolygonHitboxComponent* phc = createPolygonHitboxComponent(npc->getId());
    kantan::MovementComponent* mc = createMovementComponent(npc->getId());

    // Configure the components.
    phc->points = {
            sf::Vector2f(0.f, 0.f),
            sf::Vector2f(31.f, 0.f),
            sf::Vector2f(31.f, 48.f),
            sf::Vector2f(0.f, 48.f)
        };
    phc->computeAxes();
    phc->isBlocking = true;

    mc->maximumSpeed = 1000.f;

    // Add the components to the entity.
    npc->addComponent(phc);
    npc->addComponent(mc);

    // Return the entity.
    return npc;
}
