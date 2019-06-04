#include "StaticMarkerComponent.hpp"

StaticMarkerComponent::StaticMarkerComponent(unsigned int ownerId)
     : kantan::Component(std::string("StaticMarker"), ownerId)
     , isStatic(false)
{}
