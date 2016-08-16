#include "NameComponent.hpp"

NameComponent::NameComponent(std::size_t ownerId)
     : kantan::Component(std::string("Name"), ownerId)
     , id(-1)
     , name("#")
{}
