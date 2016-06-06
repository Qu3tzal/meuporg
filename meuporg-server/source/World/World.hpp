#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <SFML/System.hpp>

#include "../Kantan-2/kantan.hpp"

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
        void update(sf::Time dt);

    protected:
        // Removes the entities marked as to delete.
        void cleanEntities();

        // Removes a component from the component list.
        template<typename T>
        bool removeComponentFrom(kantan::Component* c, std::vector<T*>& components);

        // Creates an entity with only the deletion marker component.
        kantan::Entity* createEntity(std::string name);

        // createXXXComponent methods.
        kantan::DeletionMarkerComponent* createDeletionMarkerComponent(std::size_t ownerId);
        kantan::PolygonHitboxComponent* createPolygonHitboxComponent(std::size_t ownerId);
        kantan::MovementComponent* createMovementComponent(std::size_t ownerId);
        kantan::RotationComponent* createRotationComponent(std::size_t ownerId);

        // createXXX methods.

    protected:
        // Entities.
        std::vector<kantan::Entity*> m_entities;

        // Components.
        std::vector<kantan::DeletionMarkerComponent*> m_deletionMarkerComponents;
        std::vector<kantan::PolygonHitboxComponent*> m_polygonHitboxComponents;
        std::vector<kantan::MovementComponent*> m_movementComponents;
        std::vector<kantan::RotationComponent*> m_rotationComponents;

        // Systems.
        kantan::PolygonCollisionSystem m_collisionSystem;
        kantan::RotationSystem m_rotationSystem;
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
