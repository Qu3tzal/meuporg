#include "BasicStatsComponent.hpp"

BasicStatsComponent::BasicStatsComponent(unsigned int ownerId)
     : kantan::Component(std::string("BasicStats"), ownerId)
     , isDead(false)
     , hp(1.f)
	 , maxhp(1.f)
	 , strength(0.f)
	 , agility(0.f)
	 , resistance(0.f)
{}
