#ifndef KANTAN_PARTICLEEFFECTUPDATESYSTEM
#define KANTAN_PARTICLEEFFECTUPDATESYSTEM

#include <SFML/Graphics.hpp>
#include <vector>

#include "System.hpp"
#include "../Component/ParticleEffectComponent.hpp"

namespace kantan
{
    /*
        Particle effect update system.
    */
    class ParticleEffectUpdateSystem : public kantan::System
    {
        public:
            // Ctor.
            ParticleEffectUpdateSystem();

            // Update.
            virtual void update(std::vector<kantan::Component*>& particleEffectComponents, sf::Time dt);
    };
} // namespace kantan.

#endif // KANTAN_PARTICLEEFFECTUPDATESYSTEM
