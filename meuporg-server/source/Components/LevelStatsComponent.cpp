#include "LevelStatsComponent.hpp"

LevelStatsComponent::LevelStatsComponent(unsigned long long ownerId)
     : kantan::Component(std::string("LevelStats"), ownerId)
     , xp(0.f)
	 , level(0.f)
{}
