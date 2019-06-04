#ifndef KANTAN_BATCHEDSPRITECOMPONENT
#define KANTAN_BATCHEDSPRITECOMPONENT

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace kantan
{
    /*
        Batched sprite component.
    */
    class BatchedSpriteComponent : public kantan::Component
    {
        public:
            // Ctor.
            BatchedSpriteComponent(unsigned int ownerId);

            // Attribute.
            sf::Texture* texturePtr;
            sf::IntRect textureCoords;
            sf::FloatRect hitbox;
            float rotation;
    };
} // namespace kantan.

#endif // KANTAN_BATCHEDSPRITECOMPONENT
