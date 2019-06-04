#include "MovementComponent.hpp"

#include <string>

namespace kantan
{
    MovementComponent::MovementComponent(unsigned long long ownerId)
            : kantan::Component(std::string("Movement"), ownerId)
            , maximumSpeed(700.f)
    {}
} // namespace kantan.
