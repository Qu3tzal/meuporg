#include "RotationSystem.hpp"

namespace kantan
{
    // Ctor.
    RotationSystem::RotationSystem()
    {}

    // Update.
    void RotationSystem::update(sf::Time dt, std::vector<kantan::Component*>& polygonHitboxComponents, std::vector<kantan::Component*>& rotationComponents)
    {
        for(kantan::Component* component : rotationComponents)
        {
            kantan::RotationComponent* rc = static_cast<kantan::RotationComponent*>(component);

            // We look for the corresponding AABB hitbox component, if it exists.
            kantan::PolygonHitboxComponent* phc = Component::getFirstComponentOwnedBy<kantan::PolygonHitboxComponent>(rc->getOwnerId(), polygonHitboxComponents);

            // If none found, next rotation component.
            if(phc == nullptr)
                continue;

			// Update hitbox's position with rotation.
			sf::Transform transformation;
			rc->rotationVelocity += rc->rotationAcceleration * dt.asSeconds();

			if(rc->maximumRotationSpeed >= 0)
                rc->rotationVelocity = std::copysign(std::min(std::abs(rc->rotationVelocity), rc->maximumRotationSpeed), rc->rotationVelocity);

			float rotationDelta = rc->rotationVelocity * dt.asSeconds();

			// Reset the rotation acceleration.
            rc->rotationAcceleration = 0.f;

			if(rotationDelta != 0.f)
			{
				rc->rotation += rotationDelta;

				// Apply the rotation from the center of the hitbox.
				sf::Vector2f center(0.f, 0.f);
				for(sf::Vector2f point : phc->points)
					center += point;
				center /= (float)(phc->points.size());

				transformation.rotate(rotationDelta, center);

				// We don't apply rotation to AABB hitboxes.
				for(sf::Vector2f& point : phc->points)
					point = transformation.transformPoint(point);
			}

			// Update the separation axes.
			phc->computeAxes();
        }
    }
} // namespace kantan.
