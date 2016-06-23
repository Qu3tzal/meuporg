#ifndef KANTAN_BATCHEDSPRITERENDERSYSTEM
#define KANTAN_BATCHEDSPRITERENDERSYSTEM

#include <SFML/Graphics.hpp>
#include <vector>

#include "../Platform.hpp"
#include "System.hpp"
#include "../Component/BatchedSpriteComponent.hpp"
#include "../Utils/MathUtils.hpp"

namespace kantan
{
    /*
        Batched sprite rendering system.
    */
    class BatchedSpriteRenderSystem : public kantan::System
    {
        public:
            // Ctor.
            BatchedSpriteRenderSystem(sf::RenderWindow* window);

            // Update.
            virtual void update(std::vector<kantan::Component*>& batchedSpriteComponents);

        protected:
            // Window ptr.
            sf::RenderWindow* m_window;
    };
} // namespace kantan.

#endif // KANTAN_BATCHEDSPRITERENDERSYSTEM
