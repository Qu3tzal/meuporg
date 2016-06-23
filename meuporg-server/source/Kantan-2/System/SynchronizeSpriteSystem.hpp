#ifndef KANTAN_SYNCHRONIZESPRITESYSTEM
#define KANTAN_SYNCHRONIZESPRITESYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Utils/GraphicsUtils.hpp"
#include "../Component/AABBHitboxComponent.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/SpriteComponent.hpp"

namespace kantan
{
    /*
        SynchronizeSpriteSystem.
        This system synchronize the rendering position with the hitbox position, if any.
    */
    class SynchronizeSpriteSystem : public kantan::System
    {
        public:
            // Ctor.
            SynchronizeSpriteSystem();

            // Update.
            virtual void updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& spriteComponents);
            virtual void updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& spriteComponents);
    };
} // namespace kantan.

#endif // KANTAN_SYNCHRONIZESPRITESYSTEM
