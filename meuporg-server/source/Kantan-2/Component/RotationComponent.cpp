#include "RotationComponent.hpp"

#include <string>

namespace kantan
{
    RotationComponent::RotationComponent(unsigned long long ownerId)
            : kantan::Component(std::string("Rotation"), ownerId)
            , rotationAcceleration(0.f)
            , rotationVelocity(0.f)
			, rotation(0.f)
			, maximumRotationSpeed(100.f)
    {}
} // namespace kantan.
