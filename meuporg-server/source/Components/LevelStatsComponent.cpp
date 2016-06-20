#include "LevelStatsComponent.hpp"

LevelStatsComponent::LevelStatsComponent(std::size_t ownerId)
     : kantan::Component(std::string("LevelStats"), ownerId)
     , xp(0.f)
	 , level(0.f)
{}
