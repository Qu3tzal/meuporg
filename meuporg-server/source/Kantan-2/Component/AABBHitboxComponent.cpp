#include "AABBHitboxComponent.hpp"

namespace kantan
{
    AABBHitboxComponent::AABBHitboxComponent(std::size_t ownerId)
                : kantan::Component(std::string("AABBHitbox"), ownerId)
                , isBlocking(true)
    {}

} // namespace kantan.
