#include "MovementComponent.hpp"

#include <string>

namespace kantan
{
    MovementComponent::MovementComponent(std::size_t ownerId)
            : kantan::Component(std::string("Movement"), ownerId)
            , maximumSpeed(700.f)
    {}
} // namespace kantan.
