#include "RotationComponent.hpp"

#include <string>

namespace kantan
{
    RotationComponent::RotationComponent(std::size_t ownerId)
            : kantan::Component(std::string("Rotation"), ownerId)
            , rotationAcceleration(0.f)
            , rotationVelocity(0.f)
			, rotation(0.f)
			, maximumRotationSpeed(100.f)
    {}
} // namespace kantan.
