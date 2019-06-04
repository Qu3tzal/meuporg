#include "NameComponent.hpp"

NameComponent::NameComponent(unsigned int ownerId)
     : kantan::Component(std::string("Name"), ownerId)
     , id(-1)
     , name("#")
{}
