#ifndef KANTAN_SPRITERENDERSYSTEM
#define KANTAN_SPRITERENDERSYSTEM

#include <SFML/Graphics.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/SpriteComponent.hpp"

namespace kantan
{
    /*
        Sprite rendering system.
    */
    class SpriteRenderSystem : public kantan::System
    {
        public:
            // Ctor.
            SpriteRenderSystem(sf::RenderWindow* window);

            // Update.
            virtual void update(std::vector<kantan::SpriteComponent*>& spriteComponents);

        protected:
            // Window ptr.
            sf::RenderWindow* m_window;
    };
} // namespace kantan.

#endif // KANTAN_SPRITERENDERSYSTEM
