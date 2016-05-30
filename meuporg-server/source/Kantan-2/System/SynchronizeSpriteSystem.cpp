#include "SynchronizeSpriteSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeSpriteSystem::SynchronizeSpriteSystem()
    {}

    // Update.
    void SynchronizeSpriteSystem::update(std::vector<kantan::AABBHitboxComponent*>& aabbHitboxComponents, std::vector<kantan::SpriteComponent*>& spriteComponents)
    {
        for(kantan::AABBHitboxComponent* hc : aabbHitboxComponents)
        {
            // We look for the corresponding sprite component, if it exists.
            kantan::SpriteComponent* sc = Component::getFirstComponentOwnedBy<kantan::SpriteComponent>(hc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(sc == nullptr)
                continue;

            // Update sprite's position with hitbox's position.
            sc->sprite.setPosition(hc->hitbox.left, hc->hitbox.top);
        }
    }

    void SynchronizeSpriteSystem::update(std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::SpriteComponent*>& spriteComponents)
    {
        for(kantan::PolygonHitboxComponent* phc : polygonHitboxComponents)
        {
            // We look for the corresponding sprite component, if it exists.
            kantan::SpriteComponent* sc = Component::getFirstComponentOwnedBy<kantan::SpriteComponent>(phc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(sc == nullptr)
                continue;

            // Update sprite's position with hitbox's position.
            sc->sprite.setPosition(getCenter<float>(phc->points));
        }
    }
} // namespace kantan.
