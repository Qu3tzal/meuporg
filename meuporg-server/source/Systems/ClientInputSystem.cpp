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

            // Get the basic stats component.
            BasicStatsComponent* bsc = entity->getComponent<BasicStatsComponent>("BasicStats");

            // Get the level stats component.
            LevelStatsComponent* lsc = entity->getComponent<LevelStatsComponent>("LevelStats");

            // Get the weapon component.
            WeaponComponent *wc = entity->getComponent<WeaponComponent>("Weapon");

            // A player MUST have these components.
            if(phc == nullptr || mc == nullptr || bsc == nullptr || lsc == nullptr || wc == nullptr)
                continue;


            // Block input if dead.
            if(bsc->isDead)
            {
                mc->velocity = sf::Vector2f(0.f, 0.f);
                continue;
            }

            // Movement.
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

            // Attacks.
            if(clc->client->inputs.isAAttackKeyPressed)
            {
                if(wc->timeSinceLastShot >= wc->cooldown)
                {
                    wc->timeSinceLastShot = sf::Time::Zero;

                    sf::Vector2f center = kantan::getCenter(phc->points);
                    sf::Vector2f direction = sf::Vector2f(clc->client->inputs.mouseX, clc->client->inputs.mouseY) - center;

                    world->createBullet(
                                    kantan::getCenter(phc->points) + kantan::normalize(direction),
                                    entity->getId(),
                                    direction,
                                    wc->projectileSpeed,
                                    wc->baseDamage + wc->baseDamage * (std::min(lsc->level, 100.f) / 100.f),
                                    wc->projectileLifetime
                                );
                }
            }
        }
    }
}
