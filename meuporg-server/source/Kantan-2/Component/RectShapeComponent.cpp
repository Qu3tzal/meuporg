#include "RectShapeComponent.hpp"

#include <string>

namespace kantan
{
    RectShapeComponent::RectShapeComponent(unsigned long long ownerId)
         : kantan::Component(std::string("RectShape"), ownerId)
    {}
} // namespace kantan.
