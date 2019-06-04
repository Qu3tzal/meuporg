#include "LifetimeComponent.hpp"

LifetimeComponent::LifetimeComponent(unsigned long long ownerId)
     : kantan::Component(std::string("Lifetime"), ownerId)
	 , maxlifetime(sf::seconds(1.f))
	 , lifetime(sf::Time::Zero)
{}
