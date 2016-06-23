#include "SpriteRenderSystem.hpp"

namespace kantan
{
    // Ctor.
    SpriteRenderSystem::SpriteRenderSystem(sf::RenderWindow* window)
        : m_window(window)
    {}

    // Update.
    void SpriteRenderSystem::update(std::vector<kantan::Component*>& spriteComponents)
    {
        // View hitbox.
        sf::FloatRect viewHitbox(0.f, 0.f, m_window->getView().getSize().x, m_window->getView().getSize().y);

        for(kantan::Component* component : spriteComponents)
        {
            kantan::SpriteComponent* sc = static_cast<kantan::SpriteComponent*>(component);

            // Get the sprite component and render it.
            if(viewHitbox.intersects(sc->sprite.getGlobalBounds()))
                m_window->draw(sc->sprite);
        }
    }
} // namespace kantan.
