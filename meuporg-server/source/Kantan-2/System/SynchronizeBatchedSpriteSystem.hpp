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
            virtual void update(std::vector<kantan::AABBHitboxComponent*>& aabbHitboxComponents, std::vector<kantan::BatchedSpriteComponent*>& spriteComponents);
            virtual void update(std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::BatchedSpriteComponent*>& spriteComponents, std::vector<kantan::RotationComponent*>& rotationComponents);
    };
} // namespace kantan.

#endif // KANTAN_SYNCHRONIZEBATCHEDSPRITESYSTEM
