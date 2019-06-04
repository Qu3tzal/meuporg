#include "ParticleEffectComponent.hpp"

namespace kantan
{
    ParticleEffectComponent::ParticleEffectComponent(unsigned long long ownerId)
                : kantan::Component(std::string("ParticleEffect"), ownerId)
    {}

} // namespace kantan.
