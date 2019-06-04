#ifndef BONUSCOMPONENT_HPP_INCLUDED
#define BONUSCOMPONENT_HPP_INCLUDED

#include <functional>

#include "../Kantan-2/kantan.hpp"
#include "BasicStatsComponent.hpp"

/*
	BonusComponent class.
	Component : apply a bonus effect on a given BasicStatsComponent.
*/
class BonusComponent : public kantan::Component
{
	public:
		// Ctor.
		BonusComponent(unsigned int ownerId);

		// Attribute.
		std::function<void(BasicStatsComponent*)> effect;
};

#endif // BONUSCOMPONENT_HPP_INCLUDED
