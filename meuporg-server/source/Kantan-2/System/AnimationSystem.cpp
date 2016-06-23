#include "AnimationSystem.hpp"

namespace kantan
{
    // Ctor.
    AnimationSystem::AnimationSystem(){}

    // Update.
    void AnimationSystem::update(sf::Time elapsed, std::vector<kantan::Component*>& spriteComponents, std::vector<kantan::Component*>& animationComponents)
    {
        for(kantan::Component* component : spriteComponents)
        {
            kantan::SpriteComponent* sc = static_cast<kantan::SpriteComponent*>(component);

            // We look for the corresponding animation component, if it exists.
            kantan::AnimationComponent* ac = Component::getFirstComponentOwnedBy<kantan::AnimationComponent>(sc->getOwnerId(), animationComponents);

            // If none found, next sprite component.
            if(ac == nullptr)
                continue;

            // Update time since last frame.
            ac->lastFrame += elapsed;

            // Check if we need to change frame.
            if(ac->lastFrame > sf::seconds(1.f/(ac->fps)))
            {
                // Reset time since last frame.
                ac->lastFrame = sf::Time::Zero;

                // Change the frame index.
                if(ac->currentFrame + 1 >= ac->frames.size())
                    ac->currentFrame = 0;
                else
                    ac->currentFrame++;

                // Get the next frame and apply it to the sprite.
                sc->sprite.setTextureRect(ac->frames[ac->currentFrame]);
            }
        }
    }
} // namespace kantan.
