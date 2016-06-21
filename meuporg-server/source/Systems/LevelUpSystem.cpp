#include "LevelUpSystem.hpp"

// Ctor.
LevelUpSystem::LevelUpSystem(){}

// Update.
void LevelUpSystem::update(std::vector<LevelStatsComponent*>& levelStatsComponents, std::function<void(LevelStatsComponent*)> callback)
{
    for(LevelStatsComponent* lsc : levelStatsComponents)
    {
		float levelCache = lsc->level;

        while(lsc->xp >= 100.f)
		{
			lsc->xp -= 100.f;
			lsc->level++;
		}

		if(levelCache != lsc->level)
			callback(lsc);
    }
}
