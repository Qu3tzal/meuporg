#ifndef KANTAN_PARTICLEEFFECTRENDERSYSTEM
#define KANTAN_PARTICLEEFFECTRENDERSYSTEM

#include <SFML/Graphics.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/ParticleEffectComponent.hpp"

namespace kantan
{
    /*
        Particle effect rendering system.
    */
    class ParticleEffectRenderSystem : public kantan::System
    {
        public:
            // Ctor.
            ParticleEffectRenderSystem(sf::RenderWindow* window);

            // Update.
            virtual void update(std::vector<kantan::ParticleEffectComponent*>& particleEffectComponents);

        protected:
            // Window ptr.
            sf::RenderWindow* m_window;
    };
} // namespace kantan.

#endif // KANTAN_PARTICLEEFFECTRENDERSYSTEM
