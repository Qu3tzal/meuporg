#include "SpriteComponent.hpp"

#include <string>

namespace kantan
{
    SpriteComponent::SpriteComponent(std::size_t ownerId)
         : kantan::Component(std::string("Sprite"), ownerId)
    {}
} // namespace kantan.
