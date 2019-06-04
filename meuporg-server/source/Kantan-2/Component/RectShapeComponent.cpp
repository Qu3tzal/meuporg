#include "RectShapeComponent.hpp"

#include <string>

namespace kantan
{
    RectShapeComponent::RectShapeComponent(unsigned int ownerId)
         : kantan::Component(std::string("RectShape"), ownerId)
    {}
} // namespace kantan.
