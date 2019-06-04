#include "DamageComponent.hpp"

DamageComponent::DamageComponent(unsigned long long ownerId)
     : kantan::Component(std::string("Damage"), ownerId)
	 , emitter(-1)
	 , damage(1.f)
{}
