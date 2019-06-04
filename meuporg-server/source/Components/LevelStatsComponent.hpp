#ifndef LEVELSTATSCOMPONENT_HPP_INCLUDED
#define LEVELSTATSCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	LevelStatsComponent class.
	Component : holds the xp and level.
*/
class LevelStatsComponent : public kantan::Component
{
	public:
		// Ctor.
		LevelStatsComponent(unsigned int ownerId);

		// Attribute.
		float xp;
		float level;
};

#endif // LEVELSTATSCOMPONENT_HPP_INCLUDED
