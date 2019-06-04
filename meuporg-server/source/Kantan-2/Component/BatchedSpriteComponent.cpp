#include "BatchedSpriteComponent.hpp"

#include <string>

namespace kantan
{
    BatchedSpriteComponent::BatchedSpriteComponent(unsigned long long ownerId)
         : kantan::Component(std::string("BatchedSprite"), ownerId)
         , texturePtr(nullptr)
         , rotation(0.f)
    {}
} // namespace kantan.
