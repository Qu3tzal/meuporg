#ifndef KANTAN_SPRITECOMPONENT
#define KANTAN_SPRITECOMPONENT

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Sprite component.
    */
    class SpriteComponent : public kantan::Component
    {
        public:
            // Ctor.
            SpriteComponent(std::size_t ownerId);

            // Attribute.
            sf::Sprite sprite;
    };
} // namespace kantan.

#endif // KANTAN_SPRITECOMPONENT
