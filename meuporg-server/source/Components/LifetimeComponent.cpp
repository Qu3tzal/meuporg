#include "LifetimeComponent.hpp"

LifetimeComponent::LifetimeComponent(std::size_t ownerId)
     : kantan::Component(std::string("Lifetime"), ownerId)
	 , maxlifetime(sf::seconds(1.f))
	 , lifetime(sf::Time::Zero)
{}
