#include "MonsterAIComponent.hpp"

MonsterAIComponent::MonsterAIComponent(unsigned int ownerId)
     : kantan::Component(std::string("MonsterAI"), ownerId)
     , direction(1)
     , lastDecision(sf::Time::Zero)
{}
