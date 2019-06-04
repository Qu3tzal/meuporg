#include "NameComponent.hpp"

NameComponent::NameComponent(unsigned long long ownerId)
     : kantan::Component(std::string("Name"), ownerId)
     , id(-1)
     , name("#")
{}
