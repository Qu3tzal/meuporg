#ifndef MONSTERAICOMPONENT_HPP_INCLUDED
#define MONSTERAICOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	MonsterAIComponent class.
	Component : holds direction and last decision.
*/
class MonsterAIComponent : public kantan::Component
{
	public:
		// Ctor.
		MonsterAIComponent(unsigned long long ownerId);

		// Attribute.
		int direction;
		sf::Time lastDecision;
};

#endif // MONSTERAICOMPONENT_HPP_INCLUDED
