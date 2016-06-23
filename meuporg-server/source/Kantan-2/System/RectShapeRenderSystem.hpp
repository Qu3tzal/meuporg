#ifndef KANTAN_RECTSHAPERENDERSYSTEM
#define KANTAN_RECTSHAPERENDERSYSTEM

#include <SFML/Graphics.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/RectShapeComponent.hpp"

namespace kantan
{
    /*
        Rect shape rendering system.
    */
    class RectShapeRenderSystem : public kantan::System
    {
        public:
            // Ctor.
            RectShapeRenderSystem(sf::RenderWindow* window);

            // Update.
            virtual void update(std::vector<kantan::Component*>& rectShapeComponents);

        protected:
            // Window ptr.
            sf::RenderWindow* m_window;
    };
} // namespace kantan.

#endif // KANTAN_RECTSHAPERENDERSYSTEM
