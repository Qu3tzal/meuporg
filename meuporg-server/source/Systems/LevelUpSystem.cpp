#include "LevelUpSystem.hpp"

// Ctor.
LevelUpSystem::LevelUpSystem(){}

// Update.
void LevelUpSystem::update(std::vector<kantan::Component*>& levelStatsComponents, std::function<void(LevelStatsComponent*)> callback)
{
    for(kantan::Component* component : levelStatsComponents)
    {
        LevelStatsComponent* lsc = static_cast<LevelStatsComponent*>(component);

		float levelCache = lsc->level;

        while(lsc->xp >= 100.f)
		{
			lsc->xp -= 100.f;
			lsc->level++;
			std::cout << "[WORLD] Entity #" << lsc->getOwnerId() << " leveled up to level " << lsc->level << " !" << std::endl;
		}

		if(levelCache != lsc->level)
			callback(lsc);
    }
}
