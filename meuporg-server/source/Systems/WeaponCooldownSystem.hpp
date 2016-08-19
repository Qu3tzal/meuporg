#ifndef WEAPONCOOLDOWNSYSTEM_HPP_INCLUDED
#define WEAPONCOOLDOWNSYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/WeaponComponent.hpp"

/*
	WeaponCooldownSystem class.
	System : manages the cooldown of the weapons.
*/
class WeaponCooldownSystem : public kantan::System
{
	public:
		// Ctor.
		WeaponCooldownSystem();

		// Update.
		virtual void update(sf::Time dt, std::vector<kantan::Component*>& weaponComponents);
};

#endif // WEAPONCOOLDOWNSYSTEM_HPP_INCLUDED
