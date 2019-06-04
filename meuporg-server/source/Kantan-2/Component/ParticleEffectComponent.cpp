#include "ParticleEffectComponent.hpp"

namespace kantan
{
    ParticleEffectComponent::ParticleEffectComponent(unsigned int ownerId)
                : kantan::Component(std::string("ParticleEffect"), ownerId)
    {}

} // namespace kantan.
