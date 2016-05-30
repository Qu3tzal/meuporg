#include "SynchronizeBatchedSpriteSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeBatchedSpriteSystem::SynchronizeBatchedSpriteSystem()
    {}

    // Update.
    void SynchronizeBatchedSpriteSystem::update(std::vector<kantan::AABBHitboxComponent*>& aabbHitboxComponents, std::vector<kantan::BatchedSpriteComponent*>& spriteComponents)
    {
        for(kantan::AABBHitboxComponent* hc : aabbHitboxComponents)
        {
            // We look for the corresponding sprite component, if it exists.
            kantan::BatchedSpriteComponent* bsc = Component::getFirstComponentOwnedBy<kantan::BatchedSpriteComponent>(hc->getOwnerId(), spriteComponents);

            // If none found, next hitbox component.
            if(bsc == nullptr)
                continue;

            // Update sprite's hitbox with hitbox.
            bsc->hitbox = hc->hitbox;
        }
    }

    void SynchronizeBatchedSpriteSystem::update(std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::BatchedSpriteComponent*>& spriteComponents, std::vector<kantan::RotationComponent*>& rotationComponents)
    {
        for(kantan::PolygonHitboxComponent* phc : polygonHitboxComponents)
        {
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

