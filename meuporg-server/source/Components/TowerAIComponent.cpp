#include "TowerAIComponent.hpp"

TowerAIComponent::TowerAIComponent(unsigned long long ownerId)
     : kantan::Component(std::string("TowerAI"), ownerId)
	 , state(TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET)
	 , target(0)
{}
