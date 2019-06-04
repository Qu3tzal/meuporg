#ifndef LIFETIMECOMPONENT_HPP_INCLUDED
#define LIFETIMECOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"
#include <functional>

/*
	LifetimeComponent class.
	Component : lifetime data.
*/
class LifetimeComponent : public kantan::Component
{
	public:
		// Ctor.
		LifetimeComponent(unsigned long long ownerId);

		// Attributes.
		sf::Time maxlifetime;
		sf::Time lifetime;

		std::function<void(unsigned long long)> callback;
};

#endif // LIFETIMECOMPONENT_HPP_INCLUDED
