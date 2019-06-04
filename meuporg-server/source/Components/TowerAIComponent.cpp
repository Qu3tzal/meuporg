#include "TowerAIComponent.hpp"

TowerAIComponent::TowerAIComponent(unsigned int ownerId)
     : kantan::Component(std::string("TowerAI"), ownerId)
	 , state(TowerAIComponent::TowerAIState::LOOKING_FOR_TARGET)
	 , target(0)
{}
