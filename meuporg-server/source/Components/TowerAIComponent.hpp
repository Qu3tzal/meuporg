#ifndef TOWERAICOMPONENT_HPP_INCLUDED
#define TOWERAICOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	TowerAIComponent class.
	Component : holds the xp and level.
*/
class TowerAIComponent : public kantan::Component
{
	public:
		// State enum.
		enum TowerAIState
		{
			LOOKING_FOR_TARGET,
			SHOOTING
		};
	
	public:
		// Ctor.
		TowerAIComponent(unsigned long long ownerId);

		// Attribute.
		TowerAIState state;
		unsigned long long target;
};

#endif // TOWERAICOMPONENT_HPP_INCLUDED
