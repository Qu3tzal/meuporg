#include "DamageComponent.hpp"

DamageComponent::DamageComponent(std::size_t ownerId)
     : kantan::Component(std::string("Damage"), ownerId)
	 , emitter(-1)
	 , damage(1.f)
{}
