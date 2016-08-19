#include "ClientInputSystem.hpp"
#include "../World/World.hpp"

// Ctor.
ClientInputSystem::ClientInputSystem(){}

// Update.
void ClientInputSystem::update(std::vector<kantan::Component*>& clientLinkComponents, std::vector<kantan::Entity*>& entities, World* world)
{
    for(kantan::Component* component : clientLinkComponents)
    {
        ClientLinkComponent* clc = static_cast<ClientLinkComponent*>(component);

        // Prevent crashing.
        if(clc->client != nullptr)
        {
            kantan::Entity* entity = kantan::Entity::getEntityWithId(clc->getOwnerId(), entities);

            if(entity == nullptr)
                continue;

            // Get the hitbox component.
            kantan::PolygonHitboxComponent* phc = entity->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            // Get the movement component.
            kantan::MovementComponent* mc = entity->getComponent<kantan::MovementComponent>("Movement");

            // Get the weapon component.
            WeaponComponent *wc = entity->getComponent<WeaponComponent>("Weapon");

            // Check the entity has a movement component.
            if(entity->hasComponent("Movement"))
            {
                sf::Vector2f inputVector(0.f, 0.f);

                if(clc->client->inputs.isMoveDownKeyPressed)
                {
                    inputVector.y += 1.f;
                }
                else if(clc->client->inputs.isMoveUpKeyPressed)
                {
                    inputVector.y -= 1.f;
                }

                if(clc->client->inputs.isMoveLeftKeyPressed)
                {
                    inputVector.x -= 1.f;
                }
                else if(clc->client->inputs.isMoveRightKeyPressed)
                {
                    inputVector.x += 1.f;
                }

                mc->velocity = sf::Vector2f(0.f, 0.f);
                mc->velocity = kantan::normalize(inputVector) * mc->maximumSpeed;
            }

            if(entity->hasComponent("PolygonHitbox") && entity->hasComponent("Weapon"))
            {
                if(clc->client->inputs.isAAttackKeyPressed)
                {
                    if(wc->timeSinceLastShot >= wc->cooldown)
                    {
                        wc->timeSinceLastShot = sf::Time::Zero;

                        sf::Vector2f center = kantan::getCenter(phc->points);
                        sf::Vector2f direction = sf::Vector2f(clc->client->inputs.mouseX, clc->client->inputs.mouseY) - center;

                        world->createBullet(
                                        kantan::getCenter(phc->points) + kantan::normalize(direction) * 40.f,
                                        entity->getId(),
                                        direction,
                                        wc->projectileSpeed,
                                        wc->baseDamage,
                                        wc->projectileLifetime
                                    );
                    }
                }
            }
        }
    }
}
