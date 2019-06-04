#ifndef KANTAN_AABBCOLLISIONSYSTEM
#define KANTAN_AABBCOLLISIONSYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/AABBHitboxComponent.hpp"
#include "../Component/MovementComponent.hpp"
#include "../Utils/MathUtils.hpp"

namespace kantan
{
    /*
        Physic collision & response for AABB system.
    */
    class AABBCollisionSystem : public kantan::System
    {
        public:
            // Ctor.
            AABBCollisionSystem();

            // Update.
            virtual void update(sf::Time elapsed, std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& movementComponents);

            // Returns the collisions record.
            std::vector<std::pair<unsigned int, unsigned int>> getCollisionRecord();

        protected:
            // Record of the collisions.
            std::vector<std::pair<unsigned int, unsigned int>> m_collisions;
    };
} // namespace kantan.

#endif // KANTAN_AABBCOLLISIONSYSTEM
