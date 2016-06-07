#include "StaticMarkerComponent.hpp"

StaticMarkerComponent::StaticMarkerComponent(std::size_t ownerId)
     : kantan::Component(std::string("StaticMarker"), ownerId)
     , isStatic(false)
{}
