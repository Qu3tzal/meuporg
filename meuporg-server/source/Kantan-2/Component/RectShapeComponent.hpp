#ifndef KANTAN_RECTSHAPECOMPONENT
#define KANTAN_RECTSHAPECOMPONENT

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Rect shape component.
    */
    class RectShapeComponent : public kantan::Component
    {
        public:
            // Ctor.
            RectShapeComponent(std::size_t ownerId);

            // Attribute.
            sf::RectangleShape shape;
    };
} // namespace kantan.

#endif // KANTAN_RECTSHAPECOMPONENT
