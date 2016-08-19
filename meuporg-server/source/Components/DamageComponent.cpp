#include "DamageComponent.hpp"

DamageComponent::DamageComponent(std::size_t ownerId)
     : kantan::Component(std::string("Damage"), ownerId)
	 , damage(1.f)
{}
