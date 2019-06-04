#ifndef KANTAN_ANIMATIONCOMPONENT
#define KANTAN_ANIMATIONCOMPONENT

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Animation component.
    */
    class AnimationComponent : public kantan::Component
    {
        public:
            // Ctor.
            AnimationComponent(unsigned int ownerId);

            /// Attributes.
            // The frames subrects.
            std::vector<sf::IntRect> frames;

            // Current frame index.
            unsigned int currentFrame;

            // Time since last frame.
            sf::Time lastFrame;

            // Number of frame per seconds.
            unsigned int fps;
    };
} // namespace kantan.

#endif // KANTAN_ANIMATIONCOMPONENT
