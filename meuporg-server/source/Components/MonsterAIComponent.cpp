#include "MonsterAIComponent.hpp"

MonsterAIComponent::MonsterAIComponent(std::size_t ownerId)
     : kantan::Component(std::string("MonsterAI"), ownerId)
     , direction(1)
     , lastDecision(sf::Time::Zero)
{}
