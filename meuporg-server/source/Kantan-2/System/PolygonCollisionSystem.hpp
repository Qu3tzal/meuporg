#ifndef KANTAN_POLYGONCOLLISIONSYSTEM
#define KANTAN_POLYGONCOLLISIONSYSTEM

#include <SFML/System.hpp>

#include <functional>
#include <vector>
#include <tuple>

#include "System.hpp"
#include "../Utils/GraphicsUtils.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Utils/StringUtils.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/MovementComponent.hpp"

namespace kantan
{
    /*
        SPCell.
        Spatial Partitioning Cell.
    */
    class SPCell
    {
        public:
            // Returns true if the hitbox and the AABB intersects.
            static bool intersects(kantan::PolygonHitboxComponent* phc, sf::FloatRect AABB);

        public:
            // Ctor.
            SPCell(sf::FloatRect newAABB);

            // Dtor.
            virtual ~SPCell();

            // The AABB hitbox of the SPCell.
            sf::FloatRect AABB;

            // Components list.
            std::vector<kantan::Component*> components;

            // Removes the given component if in the list.
            void removeComponent(kantan::Component* ptr);
    };

    /*
        Physic collision & response for polygons system.
    */
    class PolygonCollisionSystem : public kantan::System
    {
        public:
            // Returns true in case of a collision.
            static bool detectCollision(kantan::PolygonHitboxComponent* a, kantan::PolygonHitboxComponent* b, sf::Vector2f& projectionVector);

        public:
            // Ctor.
            PolygonCollisionSystem();

            // Tells the spatial partitioning system that a component has been removed.
            void onComponentRemoved(kantan::Component* component);

            // Tells the spatial partitioning system that a component has been added.
            void onComponentAdded(kantan::Component* component);

            // Sets the number of cells.
            void initSpatialPartitioning(sf::Vector2i cellMapSize, float cellSize, sf::Vector2f cellMapOffset);

            // Updates the spatial partitioning.
            void updateSpatialPartitioning();

            // Update.
            virtual void update(sf::Time elapsed, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& movementComponents);

            // Resolves the collisions for a list of polygon hitboxes.
            void resolveCollisions(sf::Time elapsed, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& movementComponents);

            // Returns the collisions record.
            std::vector<std::tuple<std::size_t, std::size_t, sf::Vector2f>> getCollisionRecord();

            // Returns hitboxes near a position.
            std::vector<kantan::Component*> getNear(sf::Vector2f position, float radius);
			
			// Sets the collision response predicate.
            void setCollisionResponsePredicate(std::function<bool(std::size_t, std::size_t)> predicate);

        protected:
            // Record of the collisions.
            std::vector<std::tuple<std::size_t, std::size_t, sf::Vector2f>> m_collisions;

            // Spatial partitioning.
            sf::Vector2i m_cellMapSize;
            float m_cellSize;
            sf::Vector2f m_cellMapOffset;

            std::vector<std::vector<SPCell>> m_cellMap;
			
			// Predicate.
            std::function<bool(std::size_t, std::size_t)> m_predicate;
    };
} // namespace kantan.

#endif // KANTAN_POLYGONCOLLISIONSYSTEM
