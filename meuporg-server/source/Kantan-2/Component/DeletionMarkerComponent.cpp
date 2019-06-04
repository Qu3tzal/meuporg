#include "DeletionMarkerComponent.hpp"

#include <string>

namespace kantan
{
    DeletionMarkerComponent::DeletionMarkerComponent(unsigned long long ownerId)
         : kantan::Component(std::string("DeletionMarker"), ownerId)
         , marked(false)
    {}
} // namespace kantan.
