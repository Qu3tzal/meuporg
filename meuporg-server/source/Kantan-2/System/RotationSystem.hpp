#ifndef KANTAN_ROTATIONSYSTEM
#define KANTAN_ROTATIONSYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Utils/GraphicsUtils.hpp"
#include "../Component/AABBHitboxComponent.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/RotationComponent.hpp"

namespace kantan
{
    /*
        RotationSystem.
        This system synchronize the rendering position with the hitbox position, if any.
    */
    class RotationSystem : public kantan::System
    {
        public:
            // Ctor.
            RotationSystem();

            // Update.
            virtual void update(sf::Time dt, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& rotationComponents);
    };
} // namespace kantan.

#endif // KANTAN_ROTATIONSYSTEM
