#ifndef WEAPONCOMPONENT_HPP_INCLUDED
#define WEAPONCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	WeaponComponent class.
	Component : weapon data.
*/
class WeaponComponent : public kantan::Component
{
	public:
		// Ctor.
		WeaponComponent(std::size_t ownerId);

		// Attributes.
		std::string name;
		float baseDamage;
		float projectileSpeed;
		sf::Time cooldown;
		sf::Time timeSinceLastShot;
		sf::Time projectileLifetime;
};

#endif // WEAPONCOMPONENT_HPP_INCLUDED
