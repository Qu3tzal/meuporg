#include "AABBHitboxComponent.hpp"

namespace kantan
{
    AABBHitboxComponent::AABBHitboxComponent(unsigned int ownerId)
                : kantan::Component(std::string("AABBHitbox"), ownerId)
                , isBlocking(true)
    {}

} // namespace kantan.
