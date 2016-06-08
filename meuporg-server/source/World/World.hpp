#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <SFML/System.hpp>

#include "../Kantan-2/kantan.hpp"

#include "../Accounts.hpp"
#include "../Components/ClientLinkComponent.hpp"
#include "../Components/StaticMarkerComponent.hpp"
#include "../Systems/ClientInputSystem.hpp"
#include "../Utils/SFMLPacketUtils.hpp"
#include "../NetworkValues.hpp"
#include "../ClientEntityEnums.hpp"

class Server;

/*
    World class.
    Manages the world for a single unit.
*/
class World
{
    public:
        // Ctor.
        World();

        // Dtor.
        virtual ~World();

        // Initializes the world.
        void init();

        // Updates the world.
        void update(sf::Time dt, Server* server);

        // Creates a player instance.
        void playerConnected(Client* client);

        // Removes a player instance.
        void playerDisconnected(Client* client);

        // Sends the world state to the client.
        void sendUpdate(Client* client, sf::UdpSocket& socket);

    protected:
        // Removes the entities marked as to delete.
        void cleanEntities(Server* server);

        // Removes a component from the component list.
        template<typename T>
        bool removeComponentFrom(kantan::Component* c, std::vector<T*>& components);

        // Creates an entity with the deletion and static marker component.
        kantan::Entity* createEntity(std::string name, bool isStatic = false);

        // createXXXComponent methods.
        kantan::DeletionMarkerComponent* createDeletionMarkerComponent(std::size_t ownerId);
        kantan::PolygonHitboxComponent* createPolygonHitboxComponent(std::size_t ownerId);
        kantan::MovementComponent* createMovementComponent(std::size_t ownerId);
        kantan::RotationComponent* createRotationComponent(std::size_t ownerId);

        ClientLinkComponent* createClientLinkComponent(std::size_t ownerId);
        StaticMarkerComponent* createStaticMarkerComponent(std::size_t ownerId);

        // createXXX methods.
        kantan::Entity* createPlayer(sf::Vector2f position, Client* client);
        kantan::Entity* createNPC(sf::Vector2f position);
        kantan::Entity* createBox(sf::Vector2f position);

    protected:
        // Entities.
        std::vector<kantan::Entity*> m_entities;

        // Components.
        std::vector<kantan::DeletionMarkerComponent*> m_deletionMarkerComponents;
        std::vector<kantan::PolygonHitboxComponent*> m_polygonHitboxComponents;
        std::vector<kantan::MovementComponent*> m_movementComponents;
        std::vector<kantan::RotationComponent*> m_rotationComponents;

        std::vector<ClientLinkComponent*> m_clientLinkComponents;
        std::vector<StaticMarkerComponent*> m_staticMarkerComponents;

        // Systems.
        kantan::PolygonCollisionSystem m_collisionSystem;
        kantan::RotationSystem m_rotationSystem;

        ClientInputSystem m_clientInputSystem;
};

template<typename T>
bool World::removeComponentFrom(kantan::Component* c, std::vector<T*>& components)
{
    auto itr = std::find_if(components.begin(), components.end(), [c](kantan::Component* nc){
                                    return c == nc;
                                });

    if(itr != components.end())
    {
        components.erase(itr);
        return true;
    }

    return false;
}

#endif // WORLD_HPP_INCLUDED
