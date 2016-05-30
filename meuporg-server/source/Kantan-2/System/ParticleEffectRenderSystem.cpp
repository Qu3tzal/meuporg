#include "ParticleEffectRenderSystem.hpp"

namespace kantan
{
    // Ctor.
    ParticleEffectRenderSystem::ParticleEffectRenderSystem(sf::RenderWindow* window)
        : m_window(window)
    {}

    // Update.
    void ParticleEffectRenderSystem::update(std::vector<kantan::ParticleEffectComponent*>& particleEffectComponents)
    {
        // View hitbox.
        sf::FloatRect viewHitbox(0.f, 0.f, m_window->getView().getSize().x, m_window->getView().getSize().y);

        for(kantan::ParticleEffectComponent* pec : particleEffectComponents)
        {
            sf::VertexArray va(sf::PrimitiveType::Points);

            // Get the particles and add it to the vertex array if visible.
            for(kantan::Particle& particle : pec->particles)
            {
                if(viewHitbox.contains(particle.position))
                {
                    sf::Vertex vertex;
                    vertex.position = particle.position;
                    vertex.color = particle.color;

                    va.append(vertex);
                }
            }

            m_window->draw(va);
        }
    }
} // namespace kantan.
