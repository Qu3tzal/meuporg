#include "ParticleEffectComponent.hpp"

namespace kantan
{
    ParticleEffectComponent::ParticleEffectComponent(std::size_t ownerId)
                : kantan::Component(std::string("ParticleEffect"), ownerId)
    {}

} // namespace kantan.
