#ifndef LEVELUPSYSTEM_HPP_INCLUDED
#define LEVELUPSYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/LevelStatsComponent.hpp"

#include <functional>

/*
	LevelUpSystem class.
	System : level up system.
*/
class LevelUpSystem : public kantan::System
{
	public:
		// Ctor.
		LevelUpSystem();

		// Update.
		virtual void update(std::vector<kantan::Component*>& levelStatsComponents, std::function<void(LevelStatsComponent*)> callback);
};

#endif // LEVELUPSYSTEM_HPP_INCLUDED
