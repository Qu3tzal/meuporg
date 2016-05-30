#include "SynchronizeRectShapeSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeRectShapeSystem::SynchronizeRectShapeSystem()
    {}

    // Update.
    void SynchronizeRectShapeSystem::update(std::vector<kantan::AABBHitboxComponent*>& aabbHitboxComponents, std::vector<kantan::RectShapeComponent*>& rectShapeComponents)
    {
        for(kantan::AABBHitboxComponent* hc : aabbHitboxComponents)
        {
            // We look for the corresponding rect shape component, if it exists.
            kantan::RectShapeComponent* rsc = Component::getFirstComponentOwnedBy<kantan::RectShapeComponent>(hc->getOwnerId(), rectShapeComponents);

            // If none found, next hitbox component.
            if(rsc == nullptr)
                continue;

            // Update shape's position with hitbox's position.
            rsc->shape.setPosition(hc->hitbox.left, hc->hitbox.top);
        }
    }

    void SynchronizeRectShapeSystem::update(std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::RectShapeComponent*>& rectShapeComponents)
    {
        for(kantan::PolygonHitboxComponent* phc : polygonHitboxComponents)
        {
            // We look for the corresponding rect shape component, if it exists.
            kantan::RectShapeComponent* rsc = Component::getFirstComponentOwnedBy<kantan::RectShapeComponent>(phc->getOwnerId(), rectShapeComponents);

            // If none found, next hitbox component.
            if(rsc == nullptr)
                continue;

            // Update shape's position with hitbox's position.
            rsc->shape.setPosition(getCenter<float>(phc->points));
        }
    }
} // namespace kantan.
