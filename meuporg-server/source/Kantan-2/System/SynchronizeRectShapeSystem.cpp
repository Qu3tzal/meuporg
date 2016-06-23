#include "SynchronizeRectShapeSystem.hpp"

namespace kantan
{
    // Ctor.
    SynchronizeRectShapeSystem::SynchronizeRectShapeSystem()
    {}

    // Update.
    void SynchronizeRectShapeSystem::updateAABB(std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& rectShapeComponents)
    {
        for(kantan::Component* component : aabbHitboxComponents)
        {
            kantan::AABBHitboxComponent* hc = static_cast<kantan::AABBHitboxComponent*>(component);

            // We look for the corresponding rect shape component, if it exists.
            kantan::RectShapeComponent* rsc = Component::getFirstComponentOwnedBy<kantan::RectShapeComponent>(hc->getOwnerId(), rectShapeComponents);

            // If none found, next hitbox component.
            if(rsc == nullptr)
                continue;

            // Update shape's position with hitbox's position.
            rsc->shape.setPosition(hc->hitbox.left, hc->hitbox.top);
        }
    }

    void SynchronizeRectShapeSystem::updatePolygon(std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& rectShapeComponents)
    {
        for(kantan::Component* component : polygonHitboxComponents)
        {
            kantan::PolygonHitboxComponent* phc = static_cast<kantan::PolygonHitboxComponent*>(component);

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
