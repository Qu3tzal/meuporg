#include "SynchronizeSpriteSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeSpriteSystem::SynchronizeSpriteSystem()
    {}

    // Update.
    void SynchronizeSpriteSystem::updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& spriteComponents)
    {
        for(kantan::Component* component : aabbHitboxComponents)
        {
            kantan::AABBHitboxComponent* hc = static_cast<kantan::AABBHitboxComponent*>(component);

            // We look for the corresponding sprite component, if it exists.
            kantan::SpriteComponent* sc = Component::getFirstComponentOwnedBy<kantan::SpriteComponent>(hc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(sc == nullptr)
                continue;

            // Update sprite's position with hitbox's position.
            sc->sprite.setPosition(hc->hitbox.left, hc->hitbox.top);
        }
    }

    void SynchronizeSpriteSystem::updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& spriteComponents)
    {
        for(kantan::Component* component : polygonHitboxComponents)
        {
            kantan::PolygonHitboxComponent* phc = static_cast<kantan::PolygonHitboxComponent*>(component);

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
