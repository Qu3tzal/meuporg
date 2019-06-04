#include "AnimationComponent.hpp"

#include <string>

namespace kantan
{
    AnimationComponent::AnimationComponent(unsigned long long ownerId)
                : kantan::Component(std::string("Animation"), ownerId)
                , currentFrame(0)
                , lastFrame(sf::Time::Zero)
            {}
} // namespace kantan.
