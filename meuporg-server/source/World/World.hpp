#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <iostream>
#include <SFML/System.hpp>

#include "../Kantan-2/kantan.hpp"

#include "../Accounts.hpp"
#include "../Multithreading.hpp"
#include "../Database/PlayerData.hpp"

#include "../Components/BasicStatsComponent.hpp"
#include "../Components/ClientLinkComponent.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/LevelStatsComponent.hpp"
#include "../Components/LifetimeComponent.hpp"
#include "../Components/NameComponent.hpp"
#include "../Components/StaticMarkerComponent.hpp"
#include "../Components/WeaponComponent.hpp"

#include "../MapLoader/MapLoader.hpp"

#include "../Systems/ClientInputSystem.hpp"
#include "../Systems/LevelUpSystem.hpp"
#include "../Systems/LifetimeSystem.hpp"
#include "../Systems/MonsterAISystem.hpp"
#include "../Systems/WeaponCooldownSystem.hpp"

#include "../Utils/Maths.hpp"
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
        void init(std::string mapFilepath);

        // Returns the map's id.
        int getMapId() const;

        // Updates the world.
        void update(sf::Time dt, Server* server);

        // Creates a player instance.
        void playerConnected(Client* client, Server* server);

        // Removes a player instance.
        void playerDisconnected(Client* client, Server* server);

        // Sends the world state to the client.
        void sendUpdate(Client* client, sf::UdpSocket& socket);

        // Gives the given amount of XP to the player.
        void giveXpTo(std::string username, float amount);

    protected:
        // Needs this friendship to access createXXX methods.
        friend MapLoader;
        friend Server;
        friend ClientInputSystem;

        // Returns the entity pointer or nullptr if not found by its id.
        kantan::Entity* getEntity(const std::size_t& id);

        // Checks the performances of the world thread.
        void performancesCheck(sf::Time serverdt);

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
        kantan::Entity* createPlayer(sf::Vector2f position, Client* client, PlayerData playerData);
        kantan::Entity* createNPC(sf::Vector2f position);
        kantan::Entity* createBox(sf::Vector2f position);
        kantan::Entity* createMonster(sf::Vector2f position);
        kantan::Entity* createBullet(sf::Vector2f position, std::size_t emitter, sf::Vector2f direction, float maxSpeed, float damage, sf::Time projectileLifetime);

        // Notifies all the clients of the level up.
        void notifyLevelUp(LevelStatsComponent* lsc);

        // Notifies all the clients of the kill.
        void notifyKill(std::size_t killerId, std::size_t killedId);

        // Predicate for the physics engine.
        bool collisionResponsePredicate(const std::size_t& firstEntityId, const std::size_t& secondEntityId);

        // Checks the collisions.
        void checkCollisionEffects(const std::vector<std::pair<std::size_t, std::size_t>>& collisionRecord);

    protected:
        // ID.
        int m_id;

        // Map id.
        int m_mapId;

        // Inner clock.
        sf::Clock m_worldClock;
        sf::Time m_worldTimeAccumulator;
        sf::Time m_serverTimeAccumulator;

        // Entities.
        std::vector<kantan::Entity*> m_entities;

        // Components.
        std::map<std::string, std::vector<kantan::Component*>> m_components;

        // Systems.
        kantan::PolygonCollisionSystem m_collisionSystem;
        kantan::RotationSystem m_rotationSystem;

        ClientInputSystem m_clientInputSystem;
        LevelUpSystem m_levelUpSystem;
        LifetimeSystem m_lifetimeSystem;
        MonsterAISystem m_monsterAISystem;
        WeaponCooldownSystem m_weaponCooldownSystem;
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
