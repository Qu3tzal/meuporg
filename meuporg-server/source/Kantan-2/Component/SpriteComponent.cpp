#include "SpriteComponent.hpp"

#include <string>

namespace kantan
{
    SpriteComponent::SpriteComponent(unsigned int ownerId)
         : kantan::Component(std::string("Sprite"), ownerId)
    {}
} // namespace kantan.
