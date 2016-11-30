#include "TowerAISystem.hpp"
#include "../World/World.hpp"

// Ctor.
TowerAISystem::TowerAISystem()
{
    // Random.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_rng_generator = std::default_random_engine(seed);
    m_rng_distribution = std::uniform_int_distribution<int>(0, 8);
}

// Update.
void TowerAISystem::update(World* world, sf::Time dt, kantan::PolygonCollisionSystem* collisionSystem, std::vector<kantan::Component*>& towerAIComponents, std::vector<kantan::Entity*>& entities)
{
    for(kantan::Component* component : towerAIComponents)
    {
        TowerAIComponent* taic = static_cast<TowerAIComponent*>(component);

        // Entity.
        kantan::Entity* entity = kantan::Entity::getEntityWithId(taic->getOwnerId(), entities);

        if(entity == nullptr)
            continue;

        // Get polygon hitbox component.
        kantan::PolygonHitboxComponent* phc = entity->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

        if(phc == nullptr)
            continue;

        // Get basic stats component.
        BasicStatsComponent* bsc = entity->getComponent<BasicStatsComponent>("BasicStats");

        if(bsc == nullptr)
            continue;

        // Get weapon component.
        WeaponComponent* wc = entity->getComponent<WeaponComponent>("Weapon");

        if(wc == nullptr)
            continue;

        // Check death.
        if(bsc->isDead)
            continue;

        if(taic->state == TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET)
        {
            std::vector<kantan::Component*> near = collisionSystem->getNear(kantan::getCenter(phc->points), 400.f);

            for(kantan::Component* component : near)
            {
                // Get the entity.
                kantan::Entity* nearEntity = kantan::Entity::getEntityWithId(component->getOwnerId(), entities);

                if(nearEntity->getName() == "Monster")
                {
                    // Check if the entity is dead.
                    BasicStatsComponent* bsc = nearEntity->getComponent<BasicStatsComponent>("BasicStats");

                    if(bsc == nullptr)
                        continue;

                    if(bsc->isDead)
                        continue;

                    taic->state = TowerAIComponent::TowerAIState::SHOOTING;
                    taic->target = nearEntity->getId();
                }
            }
        }
        else
        {
            // Get target entity.
            kantan::Entity* target = kantan::Entity::getEntityWithId(taic->target, entities);

            if(target == nullptr)
            {
                taic->state = TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET;
                continue;
            }

            // Get target phc.
            kantan::PolygonHitboxComponent* targetPhc = target->getComponent<kantan::PolygonHitboxComponent>("PolygonHitbox");

            if(targetPhc == nullptr)
            {
                taic->state = TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET;
                continue;
            }

            // Shoot.
            if(wc->timeSinceLastShot >= wc->cooldown)
            {
                wc->timeSinceLastShot = sf::Time::Zero;

                sf::Vector2f center = kantan::getCenter(phc->points);
                sf::Vector2f targetCenter = kantan::getCenter(targetPhc->points);
                sf::Vector2f direction = targetCenter - center;

                if(kantan::squaredEuclidianDistance(center, targetCenter) > 400.f * 400.f)
                {
                    taic->state = TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET;
                    continue;
                }

                world->createBullet(
                                kantan::getCenter(phc->points) + kantan::normalize(direction),
                                taic->getOwnerId(),
                                direction,
                                wc->projectileSpeed,
                                wc->baseDamage,
                                wc->projectileLifetime
                            );
            }
        }
    }
}
