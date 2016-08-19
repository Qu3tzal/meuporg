#ifndef LIFETIMESYSTEM_HPP_INCLUDED
#define LIFETIMESYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/LifetimeComponent.hpp"

/*
	LifetimeSystem class.
	System : manages the lifetime of objects.
*/
class LifetimeSystem : public kantan::System
{
	public:
		// Ctor.
		LifetimeSystem();

		// Update.
		virtual void update(sf::Time dt, std::vector<kantan::Component*>& lifetimeComponents);
};

#endif // LIFETIMESYSTEM_HPP_INCLUDED
