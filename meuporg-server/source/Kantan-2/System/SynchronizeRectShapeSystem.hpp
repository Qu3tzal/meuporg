#ifndef KANTAN_SYNCHRONIZERECTSHAPESYSTEM
#define KANTAN_SYNCHRONIZERECTSHAPESYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Utils/GraphicsUtils.hpp"
#include "../Component/AABBHitboxComponent.hpp"
#include "../Component/PolygonHitboxComponent.hpp"
#include "../Component/RectShapeComponent.hpp"

namespace kantan
{
    /*
        SynchronizeRectShapeSystem.
        This system synchronize the rendering position with the hitbox position, if any.
    */
    class SynchronizeRectShapeSystem : public kantan::System
    {
        public:
            // Ctor.
            SynchronizeRectShapeSystem();

            // Update.
            virtual void updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& rectShapeComponents);
            virtual void updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& rectShapeComponents);
    };
} // namespace kantan.

#endif // KANTAN_SYNCHRONIZERECTSHAPESYSTEM
