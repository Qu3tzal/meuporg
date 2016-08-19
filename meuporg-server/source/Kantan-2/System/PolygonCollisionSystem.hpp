#ifndef KANTAN_POLYGONCOLLISIONSYSTEM
#define KANTAN_POLYGONCOLLISIONSYSTEM

#include <SFML/System.hpp>

#include <functional>
#include <vector>

#include "System.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Utils/StringUtils.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/MovementComponent.hpp"

namespace kantan
{
    /*
        Physic collision & response for polygons system.
    */
    class PolygonCollisionSystem : public kantan::System
    {
        public:
            // Ctor.
            PolygonCollisionSystem();

            // Returns true in case of a collision.
            bool detectCollision(kantan::PolygonHitboxComponent* a, kantan::PolygonHitboxComponent* b, sf::Vector2f& projectionVector);

            // Update.
            virtual void update(sf::Time elapsed, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& movementComponents);

            // Returns the collisions record.
            std::vector<std::pair<std::size_t, std::size_t>> getCollisionRecord();

            // Sets the collision response predicate.
            void setCollisionResponsePredicate(std::function<bool(std::size_t, std::size_t)> predicate);

        protected:
            // Record of the collisions.
            std::vector<std::pair<std::size_t, std::size_t>> m_collisions;

            // Predicate.
            std::function<bool(std::size_t, std::size_t)> m_predicate;
    };
} // namespace kantan.

#endif // KANTAN_POLYGONCOLLISIONSYSTEM
