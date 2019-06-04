#include "MovementComponent.hpp"

#include <string>

namespace kantan
{
    MovementComponent::MovementComponent(unsigned int ownerId)
            : kantan::Component(std::string("Movement"), ownerId)
            , maximumSpeed(700.f)
    {}
} // namespace kantan.
