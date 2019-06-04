#include "StaticMarkerComponent.hpp"

StaticMarkerComponent::StaticMarkerComponent(unsigned long long ownerId)
     : kantan::Component(std::string("StaticMarker"), ownerId)
     , isStatic(false)
{}
