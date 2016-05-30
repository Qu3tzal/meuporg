#include "DeletionMarkerComponent.hpp"

#include <string>

namespace kantan
{
    DeletionMarkerComponent::DeletionMarkerComponent(std::size_t ownerId)
         : kantan::Component(std::string("DeletionMarker"), ownerId)
         , marked(false)
    {}
} // namespace kantan.
