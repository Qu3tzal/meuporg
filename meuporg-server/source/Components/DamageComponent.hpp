#ifndef DAMAGECOMPONENT_HPP_INCLUDED
#define DAMAGECOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	DamageComponent class.
	Component : damage data.
*/
class DamageComponent : public kantan::Component
{
	public:
		// Ctor.
		DamageComponent(unsigned long long ownerId);

		// Attributes.
		int emitter;
		float damage;
};

#endif // DAMAGECOMPONENT_HPP_INCLUDED
