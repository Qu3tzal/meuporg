#include "BatchedSpriteRenderSystem.hpp"

namespace kantan
{
    // Ctor.
    BatchedSpriteRenderSystem::BatchedSpriteRenderSystem(sf::RenderWindow* window)
        : m_window(window)
    {}

    // Update.
    void BatchedSpriteRenderSystem::update(std::vector<kantan::Component*>& batchedSpriteComponents)
    {
        // View hitbox.
        sf::FloatRect viewHitbox(m_window->getView().getCenter().x - m_window->getView().getSize().x / 2.f,
                                 m_window->getView().getCenter().y - m_window->getView().getSize().y / 2.f,
                                 m_window->getView().getSize().x,
                                 m_window->getView().getSize().y);

        // Map of the batched sprites lists.
        std::map<sf::Texture*, std::vector<BatchedSpriteComponent*>> batchedSprites;

        // Sort the batched sprites by common texture.
        for(kantan::Component* component : batchedSpriteComponents)
        {
            kantan::BatchedSpriteComponent* bsc = static_cast<kantan::BatchedSpriteComponent*>(component);

            // Get the batched sprite component and map it with its texture.
            if(viewHitbox.intersects(bsc->hitbox))
                batchedSprites[bsc->texturePtr].push_back(bsc);
        }

        // Display the batched sprites.
        for(auto entry : batchedSprites)
        {
            // Create the vertex arrays.
            #ifdef KANTAN_ANDROID
            sf::VertexArray va(sf::PrimitiveType::Triangles);
            #else
            sf::VertexArray va(sf::PrimitiveType::Quads);
            #endif // KANTAN_ANDROID
            sf::Texture* texturePtr = entry.second[0]->texturePtr;

            for(BatchedSpriteComponent* bsc : entry.second)
            {
                // Create the rotation transformation.
                sf::Transform rotationTransform;
                rotationTransform.rotate(bsc->rotation, kantan::centerRectangle(bsc->hitbox));

                #ifdef KANTAN_ANDROID
                sf::Vertex upperLeftTriangleA, upperLeftTriangleB, upperLeftTriangleC,
                           lowerRightTriangleA, lowerRightTriangleB, lowerRightTriangleC;

                upperLeftTriangleA.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left, bsc->hitbox.top));
                upperLeftTriangleA.texCoords = sf::Vector2f(bsc->textureCoords.left, bsc->textureCoords.top);

                upperLeftTriangleB.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left + bsc->hitbox.width, bsc->hitbox.top));
                upperLeftTriangleB.texCoords = sf::Vector2f(bsc->textureCoords.left + bsc->textureCoords.width, bsc->textureCoords.top);

                upperLeftTriangleC.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left, bsc->hitbox.top + bsc->hitbox.height));
                upperLeftTriangleC.texCoords = sf::Vector2f(bsc->textureCoords.left, bsc->textureCoords.top + bsc->textureCoords.height);

                lowerRightTriangleA.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left + bsc->hitbox.width, bsc->hitbox.top));
                lowerRightTriangleA.texCoords = sf::Vector2f(bsc->textureCoords.left + bsc->textureCoords.width, bsc->textureCoords.top);

                lowerRightTriangleB.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left + bsc->hitbox.width, bsc->hitbox.top + bsc->hitbox.height));
                lowerRightTriangleB.texCoords = sf::Vector2f(bsc->textureCoords.left + bsc->textureCoords.width, bsc->textureCoords.top + bsc->textureCoords.height);

                lowerRightTriangleC.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left, bsc->hitbox.top + bsc->hitbox.height);
                lowerRightTriangleC.texCoords = sf::Vector2f(bsc->textureCoords.left, bsc->textureCoords.top + bsc->textureCoords.height);

                va.append(upperLeftTriangleA);
                va.append(upperLeftTriangleB);
                va.append(upperLeftTriangleC);

                va.append(lowerRightTriangleA);
                va.append(lowerRightTriangleB);
                va.append(lowerRightTriangleC);
                #else
                sf::Vertex leftTop, rightTop, rightBottom, leftBottom;

                leftTop.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left, bsc->hitbox.top));
                leftTop.texCoords = sf::Vector2f(bsc->textureCoords.left, bsc->textureCoords.top);

                rightTop.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left + bsc->hitbox.width, bsc->hitbox.top));
                rightTop.texCoords = sf::Vector2f(bsc->textureCoords.left + bsc->textureCoords.width, bsc->textureCoords.top);

                rightBottom.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left + bsc->hitbox.width, bsc->hitbox.top + bsc->hitbox.height));
                rightBottom.texCoords = sf::Vector2f(bsc->textureCoords.left + bsc->textureCoords.width, bsc->textureCoords.top + bsc->textureCoords.height);

                leftBottom.position = rotationTransform.transformPoint(sf::Vector2f(bsc->hitbox.left, bsc->hitbox.top + bsc->hitbox.height));
                leftBottom.texCoords = sf::Vector2f(bsc->textureCoords.left, bsc->textureCoords.top + bsc->textureCoords.height);

                va.append(leftTop);
                va.append(rightTop);
                va.append(rightBottom);
                va.append(leftBottom);

                #endif // KANTAN_ANDROID
            }

            // Draw the vertex array.
            sf::RenderStates states;
            states.texture = texturePtr;
            m_window->draw(va, states);
        }
    }
} // namespace kantan.
