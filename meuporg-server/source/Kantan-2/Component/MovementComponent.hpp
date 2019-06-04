#ifndef KANTAN_MOVEMENTCOMPONENT
#define KANTAN_MOVEMENTCOMPONENT

#include <SFML/System.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Movement component.
    */
    class MovementComponent : public kantan::Component
    {
        public:
            // Ctor.
            MovementComponent(unsigned int ownerId);

            // Attributes.
            sf::Vector2f acceleration;
            sf::Vector2f velocity;

            float maximumSpeed;
    };
} // namespace kantan.

#endif // KANTAN_MOVEMENTCOMPONENT
