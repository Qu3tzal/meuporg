#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <iostream>
#include <SFML/System.hpp>

#include "../Kantan-2/kantan.hpp"

#include "../Accounts.hpp"
#include "../MultithreadingOutput.hpp"
#include "../Components/BasicStatsComponent.hpp"
#include "../Components/ClientLinkComponent.hpp"
#include "../Components/LevelStatsComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/StaticMarkerComponent.hpp"
#include "../Systems/ClientInputSystem.hpp"
#include "../Systems/LevelUpSystem.hpp"
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
        // Last id.
        static int lastId;

    public:
        // Ctor.
        World();

        // Dtor.
        virtual ~World();

        // Returns the world's id.
        int getId() const;

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

        // Gives the given amount of XP to the player.
        void giveXpTo(std::string username, float amount);

    protected:
        // Removes the entities marked as to delete.
        void cleanEntities(Server* server);

        // Removes a component from the component list.
        template<typename T>
        bool removeComponentFrom(kantan::Component* c, std::vector<T*>& components);

        // Creates an entity with the deletion and static marker component.
        kantan::Entity* createEntity(std::string name, bool isStatic = false);

        // Creates a component.
        template<typename T>
        T* createComponent(std::size_t ownerId);

        // createXXX methods.
        kantan::Entity* createPlayer(sf::Vector2f position, Client* client);
        kantan::Entity* createNPC(sf::Vector2f position);
        kantan::Entity* createBox(sf::Vector2f position);

        // Notifies all the clients of the level up.
        void notifyLevelUp(LevelStatsComponent* lsc);

    protected:
        // ID.
        int m_id;

        // Entities.
        std::vector<kantan::Entity*> m_entities;

        // Components.
        std::map<std::string, std::vector<kantan::Component*>> m_components;

        // Systems.
        kantan::PolygonCollisionSystem m_collisionSystem;
        kantan::RotationSystem m_rotationSystem;

        ClientInputSystem m_clientInputSystem;
        LevelUpSystem m_levelUpSystem;
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

template<typename T>
T* World::createComponent(std::size_t ownerId)
{
    T* component = new T(ownerId);
    m_components[component->getName()].push_back(component);

    return component;
}

#endif // WORLD_HPP_INCLUDED
