#ifndef KANTAN_ANIMATIONSYSTEM
#define KANTAN_ANIMATIONSYSTEM

#include <SFML/System.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/SpriteComponent.hpp"
#include "../Component/AnimationComponent.hpp"

namespace kantan
{
    /*
        Animation System.
    */
    class AnimationSystem : public kantan::System
    {
        public:
            // Ctor.
            AnimationSystem();

            // Update.
            virtual void update(sf::Time elapsed, std::vector<kantan::Component*>& spriteComponents, std::vector<kantan::Component*>& animationComponents);
    };
} // namespace kantan.

#endif // KANTAN_ANIMATIONSYSTEM
