#include "WeaponCooldownSystem.hpp"

// Ctor.
WeaponCooldownSystem::WeaponCooldownSystem(){}

// Update.
void WeaponCooldownSystem::update(sf::Time dt, std::vector<kantan::Component*>& weaponComponents)
{
    for(kantan::Component* component : weaponComponents)
    {
        WeaponComponent* wc = static_cast<WeaponComponent*>(component);

		wc->timeSinceLastShot += dt;
    }
}
