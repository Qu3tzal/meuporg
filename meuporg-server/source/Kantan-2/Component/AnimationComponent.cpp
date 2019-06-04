#include "AnimationComponent.hpp"

#include <string>

namespace kantan
{
    AnimationComponent::AnimationComponent(unsigned int ownerId)
                : kantan::Component(std::string("Animation"), ownerId)
                , currentFrame(0)
                , lastFrame(sf::Time::Zero)
            {}
} // namespace kantan.
