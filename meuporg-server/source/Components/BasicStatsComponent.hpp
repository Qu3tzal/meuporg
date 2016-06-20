#ifndef BASICSTATSCOMPONENT_HPP_INCLUDED
#define BASICSTATSCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	BasicStatsComponent class.
	Component : holds the hp, strength, agility and resistance.
*/
class BasicStatsComponent : public kantan::Component
{
	public:
		// Ctor.
		BasicStatsComponent(std::size_t ownerId);

		// Attribute.
		float hp;
		float maxhp;

		float strength;
		float agility;
		float resistance;
};

#endif // BASICSTATSCOMPONENT_HPP_INCLUDED
