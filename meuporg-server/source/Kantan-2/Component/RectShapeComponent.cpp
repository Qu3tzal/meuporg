#include "RectShapeComponent.hpp"

#include <string>

namespace kantan
{
    RectShapeComponent::RectShapeComponent(std::size_t ownerId)
         : kantan::Component(std::string("RectShape"), ownerId)
    {}
} // namespace kantan.
