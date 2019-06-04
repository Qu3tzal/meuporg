#include "SpriteComponent.hpp"

#include <string>

namespace kantan
{
    SpriteComponent::SpriteComponent(unsigned long long ownerId)
         : kantan::Component(std::string("Sprite"), ownerId)
    {}
} // namespace kantan.
