#include "PolygonCollisionSystem.hpp"

namespace kantan
{
    PolygonCollisionSystem::PolygonCollisionSystem(){}

    bool PolygonCollisionSystem::detectCollision(kantan::PolygonHitboxComponent* a, kantan::PolygonHitboxComponent* b, sf::Vector2f& projectionVector)
    {
        std::vector<sf::Vector2f> all_axes;
        all_axes.reserve(a->axes.size() + b->axes.size());
        all_axes.insert(all_axes.end(), a->axes.begin(), a->axes.end());
        all_axes.insert(all_axes.end(), b->axes.begin(), b->axes.end());

        std::unique(all_axes.begin(), all_axes.end());

        projectionVector = sf::Vector2f(0.f, 0.f);

        float projectionVectorLength(std::numeric_limits<float>::max());

        for(sf::Vector2f& axe : all_axes)
        {
            float a_min_value(std::numeric_limits<float>::max()), a_max_value(std::numeric_limits<float>::min()),
                  b_min_value(std::numeric_limits<float>::max()), b_max_value(std::numeric_limits<float>::min());

            for(sf::Vector2f point : a->points)
            {
                float projection = dotProduct(point, axe) / dotProduct(axe, axe);

                if(projection < a_min_value)
                    a_min_value = projection;

                if(projection > a_max_value)
                    a_max_value = projection;
            }

            for(sf::Vector2f point : b->points)
            {
                float projection = dotProduct(point, axe) / dotProduct(axe, axe);

                if(projection < b_min_value)
                    b_min_value = projection;

                if(projection > b_max_value)
                    b_max_value = projection;
            }

            /*
                    _________
                        __________
            */
            if(a_min_value <= b_min_value && a_max_value <= b_max_value && a_max_value >= b_min_value)
            {
                sf::Vector2f wayOut = axe * (a_max_value - b_min_value);
                if(getLength(wayOut) < projectionVectorLength)
                {
                    projectionVector = wayOut;
                    projectionVectorLength = getLength(projectionVector);
                }
            }

            /*
                        ___________
                    _________
            */
            else if(b_min_value <= a_min_value && b_max_value <= a_max_value && b_max_value >= a_min_value)
            {
                sf::Vector2f wayOut = axe * (a_min_value - b_max_value);
                if(getLength(wayOut) < projectionVectorLength)
                {
                    projectionVector = wayOut;
                    projectionVectorLength = getLength(projectionVector);
                }
            }

            /*
                    ________________
                        _____
            */
            else if(a_min_value <= b_min_value && a_max_value >= b_max_value)
            {
                float by_right = b_min_value - a_max_value;
                float by_left = b_max_value - a_min_value;

                if(std::abs(by_left) < std::abs(by_right))
                {
                    if(std::abs(by_left) < projectionVectorLength)
                    {
                        projectionVector = axe * by_left;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
                else
                {
                    if(std::abs(by_right) < projectionVectorLength)
                    {
                        projectionVector = axe * by_right;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
            }

            /*
                        _____
                    ________________
            */
            else if(b_min_value <= a_min_value && b_max_value >= a_max_value)
            {
                float by_right = b_min_value - a_max_value;
                float by_left = b_max_value - a_min_value;

                if(std::abs(by_left) < std::abs(by_right))
                {
                    if(std::abs(by_left) < projectionVectorLength)
                    {
                        projectionVector = axe * by_left;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
                else
                {
                    if(std::abs(by_right) < projectionVectorLength)
                    {
                        projectionVector = axe * by_right;
                        projectionVectorLength = getLength(projectionVector);
                    }
                }
            }

            /*
                    ___
                        ____

                or
                        ____
                    ___
            */
            else
            {
                projectionVector = sf::Vector2f(0.f, 0.f);
                return false;
            }
        }

        return true;
    }

    // Update.
    void PolygonCollisionSystem::update(sf::Time elapsed, std::vector<kantan::PolygonHitboxComponent*>& polygonHitboxComponents, std::vector<kantan::MovementComponent*>& movementComponents)
    {
        m_collisions.clear();

        // We check each hitbox component against all the overs.
        /// /!\ It's a naive and slow way of doing it.
        for(kantan::PolygonHitboxComponent* fstHitbox : polygonHitboxComponents)
        {
            // If this entity has no movement, it's not the one to modify.
            // We look for the corresponding movement component, if it exists.
            kantan::MovementComponent* fstMovement = Component::getFirstComponentOwnedBy<kantan::MovementComponent>(fstHitbox->getOwnerId(), movementComponents);

            // If none found, next hitbox component.
            if(fstMovement == nullptr)
                continue;

            // Apply the movement.
            fstMovement->velocity += fstMovement->acceleration * elapsed.asSeconds();

            // Reset the acceleration.
            fstMovement->acceleration = sf::Vector2f(0.f, 0.f);

            // Check we don't exceed the maximum speed.
            if(fstMovement->maximumSpeed >= 0.f && kantan::getLength(fstMovement->velocity) > fstMovement->maximumSpeed)
                fstMovement->velocity = kantan::normalize(fstMovement->velocity) * fstMovement->maximumSpeed;

            // Create a transformation with the projection vector.
            sf::Transform transform;
            transform.translate(fstMovement->velocity * elapsed.asSeconds());

            // Apply the movement transformation.
            for(std::size_t i(0) ; i < fstHitbox->points.size() ; i++)
                fstHitbox->points[i] = transform.transformPoint(fstHitbox->points[i]);

            for(kantan::PolygonHitboxComponent* sndHitbox : polygonHitboxComponents)
            {
                // Do not check against yourself.
                if(fstHitbox == sndHitbox)
                    continue;

                // The projection vector in case of a collision.
                sf::Vector2f projectionVector;

                // Is there a collision ?
                if(detectCollision(fstHitbox, sndHitbox, projectionVector))
                {
                    // Are we blocking ?
                    if(fstHitbox->isBlocking && sndHitbox->isBlocking)
                    {
                        // Create a transformation with the projection vector.
                        transform = sf::Transform::Identity;
                        transform.translate(-projectionVector);

                        // Apply the movement transformation.
                        for(std::size_t i(0) ; i < fstHitbox->points.size() ; i++)
                            fstHitbox->points[i] = transform.transformPoint(fstHitbox->points[i]);

                        // Bouncing.
                        if(projectionVector != sf::Vector2f(0.f, 0.f))
                            fstMovement->velocity = 0.2f * getLength(fstMovement->velocity) * normalize(-projectionVector / elapsed.asSeconds());

                        // Too small velocities must be canceled.
                        if(getLength(fstMovement->velocity) <= 0.1f)
                            fstMovement->velocity = sf::Vector2f(0.f, 0.f);
                    }
                }
            }
        }
    }

    // Returns the collisions record.
    std::vector<std::pair<std::size_t, std::size_t>> PolygonCollisionSystem::getCollisionRecord()
    {
        return m_collisions;
    }
} // namespace kantan.
