#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>


/*
    TileMap class.
    Manages a tile map.
*/
class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        // Constructor.
        TileMap(unsigned int width, unsigned int height);

        // Destructor.
        virtual ~TileMap();

        // Sets the texture pointer.
        void setTexturePtr(sf::Texture* ptr);

        // Sets a code for a texture rect.
        void addTextureRect(unsigned int code, sf::IntRect textureRect);

        // Sets the tiles data.
        void setTileData(std::vector<std::vector<unsigned int>> tileData);
        void setTileData(sf::Vector2u index, unsigned int value);

        // Update the tile map based on the data hold.
        void update();

    protected:
        // Draw the tile map.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        // Contains the vertices.
        sf::VertexArray m_vertices;

        // Contains the texture pointer.
        sf::Texture* m_texturePtr;

        // Contains the code <-> texture rect map.
        std::map<unsigned int, sf::IntRect> m_textureRectCode;

        // Contains the tilemap size.
        unsigned int m_width, m_height;

        // Contains the tiles data.
        std::vector<std::vector<unsigned int>> m_tileData;
};

#endif // TILEMAP_HPP
