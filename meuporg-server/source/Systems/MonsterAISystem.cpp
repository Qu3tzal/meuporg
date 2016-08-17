#include "MonsterAISystem.hpp"

// Ctor.
MonsterAISystem::MonsterAISystem()
{
    // Random.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_rng_generator = std::default_random_engine(seed);
    m_rng_distribution = std::uniform_int_distribution<int>(0, 8);
}

// Update.
void MonsterAISystem::update(sf::Time dt, std::vector<kantan::Component*>& monsterAIComponents, std::vector<kantan::Component*>& movementComponents)
{
    for(kantan::Component* component : monsterAIComponents)
    {
        MonsterAIComponent* maic = static_cast<MonsterAIComponent*>(component);
        maic->lastDecision += dt;

        kantan::MovementComponent* mc = kantan::Component::getFirstComponentOwnedBy<kantan::MovementComponent>(maic->getOwnerId(), movementComponents);

        if(mc == nullptr)
            continue;

        // Do we need to take another decision ?
        if(maic->lastDecision >= sf::seconds(0.5f))
        {
            maic->lastDecision -= sf::seconds(0.5f);
            maic->direction = m_rng_distribution(m_rng_generator);
        }
        // Keep the same decision.
        else
        {
            switch(maic->direction)
            {
                case 0:
                    mc->velocity = sf::Vector2f(mc->maximumSpeed, 0.f);
                    break;
                case 1:
                    mc->velocity = sf::Vector2f(-mc->maximumSpeed, 0.f);
                    break;
                case 2:
                    mc->velocity = sf::Vector2f(0.f, mc->maximumSpeed);
                    break;
                case 3:
                    mc->velocity = sf::Vector2f(0.f, -mc->maximumSpeed);
                    break;
                default:
                    // 1 chance on 2 to not move.
                    mc->velocity = sf::Vector2f(0.f, 0.f);
                    break;
            }
        }
    }
}
