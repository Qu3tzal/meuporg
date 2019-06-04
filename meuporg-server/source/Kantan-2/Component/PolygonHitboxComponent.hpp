#ifndef KANTAN_POLYGONHITBOXCOMPONENT
#define KANTAN_POLYGONHITBOXCOMPONENT

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Polygon hitbox component.
    */
    class PolygonHitboxComponent : public kantan::Component, public sf::Drawable
    {
        public:
            // Ctor.
            PolygonHitboxComponent(unsigned int ownerId, std::vector<sf::Vector2f> points = {});

            // Computes the axes from the points.
            void computeAxes();

            // Attributes.
            std::vector<sf::Vector2f> points;
			std::vector<sf::Vector2f> axes;
			bool isBlocking;

        protected:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
} // namespace kantan.

#endif // KANTAN_POLYGONHITBOXCOMPONENT
