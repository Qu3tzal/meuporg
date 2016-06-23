#include "AABBCollisionSystem.hpp"

namespace kantan
{
    AABBCollisionSystem::AABBCollisionSystem(){}

    // Update.
    void AABBCollisionSystem::update(sf::Time elapsed, std::vector<kantan::Component*>& aabbHitboxComponents, std::vector<kantan::Component*>& movementComponents)
    {
        m_collisions.clear();

        // We check each hitbox component against all the overs.
        /// /!\ It's a naive and slow way of doing it.
        for(kantan::Component* component : aabbHitboxComponents)
        {
            kantan::AABBHitboxComponent* fstHitbox = static_cast<kantan::AABBHitboxComponent*>(component);

            // If this entity has no movement, it's not the one to modify.
            // We look for the corresponding movement component, if it exists.
            kantan::MovementComponent* fstMovement = Component::getFirstComponentOwnedBy<kantan::MovementComponent>(fstHitbox->getOwnerId(), movementComponents);

            // If none found, next hitbox component.
            if(fstMovement == nullptr)
                continue;

            // Integrate the movement once.
            fstMovement->velocity += fstMovement->acceleration * elapsed.asSeconds();
            fstMovement->acceleration = sf::Vector2f(0.f, 0.f);

            if(kantan::getLength(fstMovement->velocity) > fstMovement->maximumSpeed)
                fstMovement->velocity = kantan::normalize(fstMovement->velocity) * fstMovement->maximumSpeed;

            for(kantan::Component* secondComponent : aabbHitboxComponents)
            {
                kantan::AABBHitboxComponent* sndHitbox = static_cast<kantan::AABBHitboxComponent*>(secondComponent);

                // Do not check against yourself.
                if(fstHitbox == sndHitbox)
                    continue;

                // We copy the fst's hitbox and apply the movement to it.
                sf::FloatRect fstNewHitbox = fstHitbox->hitbox;
                fstNewHitbox.left += fstMovement->velocity.x * elapsed.asSeconds();
                fstNewHitbox.top += fstMovement->velocity.y * elapsed.asSeconds();

                // Effective movement, will be used to compute the corrected velocity.
                sf::Vector2f movement(fstMovement->velocity.x * elapsed.asSeconds(), fstMovement->velocity.y * elapsed.asSeconds());

                // Now we check the collision & compute the movement corrections.
                if(fstNewHitbox.intersects(sndHitbox->hitbox))
                {
                    // All checks are done relatively to the fst entity.
                    // To know from where the collision comes, we look at where the hitboxes were before the movement application.
                    // If the collision is from the bottom.
                    if(fstHitbox->hitbox.top + fstHitbox->hitbox.height <= sndHitbox->hitbox.top)
                    {
                        movement.y = sndHitbox->hitbox.top - (fstHitbox->hitbox.top + fstHitbox->hitbox.height);
                    }
                    // If the collision is from the top.
                    else if(fstHitbox->hitbox.top >= sndHitbox->hitbox.top + sndHitbox->hitbox.height)
                    {
                        movement.y = -(fstHitbox->hitbox.top - (sndHitbox->hitbox.top + sndHitbox->hitbox.height));
                    }
                    // If the collision is from the right.
                    else if(fstHitbox->hitbox.left + fstHitbox->hitbox.width <= sndHitbox->hitbox.left)
                    {
                        movement.x = sndHitbox->hitbox.left - (fstHitbox->hitbox.left + fstHitbox->hitbox.width);
                    }
                    // If the collision is from the left.
                    else if(fstHitbox->hitbox.left >= sndHitbox->hitbox.left + sndHitbox->hitbox.width)
                    {
                        movement.x = -(fstHitbox->hitbox.left - (sndHitbox->hitbox.left + sndHitbox->hitbox.width));
                    }
                    // Intern collision.
                    else
                    {
                        // We'll see later what to do here.
                    }

                    // Record the collision.
                    m_collisions.push_back(std::pair<std::size_t, std::size_t>(fstHitbox->getOwnerId(), sndHitbox->getOwnerId()));

                    // Change the velocity for the next entity check if both hitboxes are blocking.
                    if(fstHitbox->isBlocking && sndHitbox->isBlocking)
                    {
                        fstMovement->velocity.x = movement.x / elapsed.asSeconds();
                        fstMovement->velocity.y = movement.y / elapsed.asSeconds();
                    }
                }
            }

            // Now we apply the corrected movement to the hitbox.
            fstHitbox->hitbox.left += fstMovement->velocity.x * elapsed.asSeconds();
            fstHitbox->hitbox.top += fstMovement->velocity.y * elapsed.asSeconds();
        }
    }

    // Returns the collisions record.
    std::vector<std::pair<std::size_t, std::size_t>> AABBCollisionSystem::getCollisionRecord()
    {
        return m_collisions;
    }
} // namespace kantan.
