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
            AnimationComponent(std::size_t ownerId);

            /// Attributes.
            // The frames subrects.
            std::vector<sf::IntRect> frames;

            // Current frame index.
            sf::Uint64 currentFrame;

            // Time since last frame.
            sf::Time lastFrame;

            // Number of frame per seconds.
            sf::Uint64 fps;
    };
} // namespace kantan.

#endif // KANTAN_ANIMATIONCOMPONENT
