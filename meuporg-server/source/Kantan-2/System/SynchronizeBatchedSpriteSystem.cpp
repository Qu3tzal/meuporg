#include "SynchronizeBatchedSpriteSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeBatchedSpriteSystem::SynchronizeBatchedSpriteSystem()
    {}

    // Update.
    void SynchronizeBatchedSpriteSystem::updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& spriteComponents)
    {
        for(kantan::Component* component : aabbHitboxComponents)
        {
            kantan::AABBHitboxComponent* hc = static_cast<kantan::AABBHitboxComponent*>(component);

            // We look for the corresponding sprite component, if it exists.
            kantan::BatchedSpriteComponent* bsc = Component::getFirstComponentOwnedBy<kantan::BatchedSpriteComponent>(hc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(bsc == nullptr)
                continue;

            // Update sprite's hitbox with hitbox.
            bsc->hitbox = hc->hitbox;
        }
    }

    void SynchronizeBatchedSpriteSystem::updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& spriteComponents, std::vector<kantan::Component*>& rotationComponents)
    {
        for(kantan::Component* component : polygonHitboxComponents)
        {
            kantan::PolygonHitboxComponent* phc = static_cast<kantan::PolygonHitboxComponent*>(component);

            // We look for the corresponding sprite component, if it exists.
            kantan::BatchedSpriteComponent* bsc = Component::getFirstComponentOwnedBy<kantan::BatchedSpriteComponent>(phc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(bsc == nullptr)
                continue;

            // We look for the corresponding rotation component, if it exists.
            kantan::RotationComponent* rc = Component::getFirstComponentOwnedBy<kantan::RotationComponent>(phc->getOwnerId(), rotationComponents);

            // If one found, apply the rotation to the sprite.
            if(rc != nullptr)
                bsc->rotation = rc->rotation;

            // Update sprite's hitbox with hitbox.
            sf::Vector2f center = getCenter<float>(phc->points);

            bsc->hitbox.left = center.x - bsc->hitbox.width / 2.f;
            bsc->hitbox.top = center.y - bsc->hitbox.height / 2.f;
        }
    }
} // namespace kantan.

