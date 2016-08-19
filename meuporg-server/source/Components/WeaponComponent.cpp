#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent(std::size_t ownerId)
     : kantan::Component(std::string("Weapon"), ownerId)
	 , name("DefaultWeapon")
	 , baseDamage(1.f)
	 , reach(1.f)
	 , projectileSpeed()
	 , cooldown(sf::seconds(1.f))
	 , timeSinceLastShot(sf::Time::Zero)
{}
