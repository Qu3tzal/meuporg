#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent(unsigned int ownerId)
     : kantan::Component(std::string("Weapon"), ownerId)
	 , name("DefaultWeapon")
	 , baseDamage(1.f)
	 , projectileSpeed()
	 , cooldown(sf::seconds(1.f))
	 , timeSinceLastShot(sf::Time::Zero)
	 , projectileLifetime(sf::seconds(1.f))
{}
