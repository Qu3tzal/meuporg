#include "RectShapeRenderSystem.hpp"

namespace kantan
{
    // Ctor.
    RectShapeRenderSystem::RectShapeRenderSystem(sf::RenderWindow* window)
        : m_window(window)
    {}

    // Update.
    void RectShapeRenderSystem::update(std::vector<kantan::RectShapeComponent*>& rectShapeComponents)
    {
        // View hitbox.
        sf::FloatRect viewHitbox(0.f, 0.f, m_window->getView().getSize().x, m_window->getView().getSize().y);

        for(kantan::RectShapeComponent* rsc : rectShapeComponents)
        {
            // Get the rect shape component and render it.
            if(viewHitbox.intersects(rsc->shape.getGlobalBounds()))
                m_window->draw(rsc->shape);
        }
    }
} // namespace kantan.
