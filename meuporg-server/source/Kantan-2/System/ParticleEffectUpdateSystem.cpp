#include "ParticleEffectUpdateSystem.hpp"

namespace kantan
{
    // Ctor.
    ParticleEffectUpdateSystem::ParticleEffectUpdateSystem()
    {}

    // Update.
    void ParticleEffectUpdateSystem::update(std::vector<kantan::ParticleEffectComponent*>& particleEffectComponents, sf::Time dt)
    {
        for(kantan::ParticleEffectComponent* pec : particleEffectComponents)
        {
            // Keep only the necessary number of particles.
            if(pec->numberOfParticles - pec->particles.size() != 0)
                pec->particles.resize(pec->numberOfParticles);

            // Update the particles.
            for(kantan::Particle& particle : pec->particles)
            {
                particle.lifetime += dt;

                // Reset particle if needed.
                if(particle.lifetime >= pec->maxLifetime)
                {
                    particle.lifetime = sf::Time::Zero;
                    particle.position = pec->emissionCenter;
                }
                else
                {
                    particle.position += particle.velocity * dt.asSeconds();
                }

                particle.velocity = pec->velocityFunction(particle, pec->emissionCenter);
                particle.color = pec->colorFunction(particle, pec->emissionCenter);
            }
        }
    }
} // namespace kantan.
