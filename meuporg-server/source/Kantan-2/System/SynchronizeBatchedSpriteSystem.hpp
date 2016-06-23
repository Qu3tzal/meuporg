#ifndef KANTAN_SYNCHRONIZEBATCHEDSPRITESYSTEM
#define KANTAN_SYNCHRONIZEBATCHEDSPRITESYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Utils/GraphicsUtils.hpp"
#include "../Utils/MathUtils.hpp"
#include "../Component/AABBHitboxComponent.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/BatchedSpriteComponent.hpp"
#include "../Component/RotationComponent.hpp"

namespace kantan
{
    /*
        SynchronizeBatchedSpriteSystem.
        This system synchronize the rendering position with the hitbox position, if any.
    */
    class SynchronizeBatchedSpriteSystem : public kantan::System
    {
        public:
            // Ctor.
            SynchronizeBatchedSpriteSystem();

            // Update.
            virtual void updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& spriteComponents);
            virtual void updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& spriteComponents, std::vector<kantan::Component*>& rotationComponents);
    };
} // namespace kantan.

#endif // KANTAN_SYNCHRONIZEBATCHEDSPRITESYSTEM
