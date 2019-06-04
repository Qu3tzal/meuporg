#ifndef KANTAN_ROTATIONCOMPONENT
#define KANTAN_ROTATIONCOMPONENT

#include <SFML/System.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Rotation component.
    */
    class RotationComponent : public kantan::Component
    {
        public:
            // Ctor.
            RotationComponent(unsigned long long ownerId);

            // Attributes.
			float rotationAcceleration;
            float rotationVelocity;
			float rotation;

			float maximumRotationSpeed;
    };
} // namespace kantan.

#endif // KANTAN_ROTATIONCOMPONENT
