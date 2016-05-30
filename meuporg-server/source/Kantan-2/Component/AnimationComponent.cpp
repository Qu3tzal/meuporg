#include "AnimationComponent.hpp"

#include <string>

namespace kantan
{
    AnimationComponent::AnimationComponent(std::size_t ownerId)
                : kantan::Component(std::string("Animation"), ownerId)
                , currentFrame(0)
                , lastFrame(sf::Time::Zero)
            {}
} // namespace kantan.
