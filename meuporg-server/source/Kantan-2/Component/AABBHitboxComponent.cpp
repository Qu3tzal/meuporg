#include "AABBHitboxComponent.hpp"

namespace kantan
{
    AABBHitboxComponent::AABBHitboxComponent(unsigned long long ownerId)
                : kantan::Component(std::string("AABBHitbox"), ownerId)
                , isBlocking(true)
    {}

} // namespace kantan.
