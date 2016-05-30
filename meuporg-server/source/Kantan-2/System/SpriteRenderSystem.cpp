#include "SpriteRenderSystem.hpp"

namespace kantan
{
    // Ctor.
    SpriteRenderSystem::SpriteRenderSystem(sf::RenderWindow* window)
        : m_window(window)
    {}

    // Update.
    void SpriteRenderSystem::update(std::vector<kantan::SpriteComponent*>& spriteComponents)
    {
        // View hitbox.
        sf::FloatRect viewHitbox(0.f, 0.f, m_window->getView().getSize().x, m_window->getView().getSize().y);

        for(kantan::SpriteComponent* sc : spriteComponents)
        {
            // Get the sprite component and render it.
            if(viewHitbox.intersects(sc->sprite.getGlobalBounds()))
                m_window->draw(sc->sprite);
        }
    }
} // namespace kantan.
