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
            virtual void update(std::vector<kantan::AABBHitboxComponent*>& aabbHitboxComponents, std::vector<kantan::SpriteComponent*>& spriteComponents);
            virtual void update(std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::SpriteComponent*>& spriteComponents);
    };
} // namespace kantan.

#endif // KANTAN_SYNCHRONIZESPRITESYSTEM
