#ifndef KANTAN_PARTICLEEFFECTCOMPONENT
#define KANTAN_PARTICLEEFFECTCOMPONENT

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "Component.hpp"

namespace kantan
{
    /*
        Particle structure.
    */
    class Particle
    {
        public:
            sf::Time lifetime;
            sf::Vector2f velocity;
            sf::Vector2f position;
            sf::Color color;
    };

    /*
        Particle effect component.
    */
    class ParticleEffectComponent : public kantan::Component
    {
        public:
            // Ctor.
            ParticleEffectComponent(unsigned long long ownerId);

            // Attributes.
            std::function<sf::Color(const Particle&, const sf::Vector2f&)> colorFunction;
            std::function<sf::Vector2f(const Particle&, const sf::Vector2f&)> velocityFunction;

            sf::Time maxLifetime;
            unsigned long long numberOfParticles;
            std::vector<Particle> particles;
            sf::Vector2f emissionCenter;
    };
} // namespace kantan.


#endif // KANTAN_PARTICLEEFFECTCOMPONENT
