#include "LifetimeSystem.hpp"

// Ctor.
LifetimeSystem::LifetimeSystem(){}

// Update.
void LifetimeSystem::update(sf::Time dt, std::vector<kantan::Component*>& lifetimeComponents)
{
    for(kantan::Component* component : lifetimeComponents)
    {
        LifetimeComponent* lc = static_cast<LifetimeComponent*>(component);

		lc->lifetime += dt;
		
		if(lc->lifetime >= lc->maxlifetime)
			lc->callback(lc->getOwnerId());
    }
}
