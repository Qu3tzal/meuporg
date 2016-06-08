#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "../ID.hpp"
#include "../TileMap/TileMap.hpp"
#include "../Tile/Tile.hpp"
#include "../ResourceId.hpp"
#include "../ResourceHolder/ResourceHolder.hpp"

/*
    Environment class.
    Manages the environment : tiles creation, drawing of the tilemap.
*/
class Environment : public sf::Drawable, public sf::Transformable
{
    public:
        // Constructor.
        Environment(TextureHolder* textures);

        // Destructor.
        virtual ~Environment();

        // Sets the tiles data.
        void setTiles(std::vector<std::vector<Tile>>& tiles);

        // Returns the tile.
        Tile getTile(sf::Vector2u index) const;

        // Returns the tile containing the position.
        sf::Vector2u getTileIndexContaining(sf::Vector2f pos) const;

    protected:
        // Draw the environment's tile map.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        // Tiles array.
        std::vector<std::vector<Tile>> m_tiles;

        // Tile map of the environment.
        TileMap m_tilemap;
};

#endif // ENVIRONMENT_HPP
