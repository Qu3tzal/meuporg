#include "Environment.hpp"

Environment::Environment(TextureHolder* textures)
    : m_tilemap(32, 32)
{
    sf::Texture* texturePtr(&textures->get(ResourceId::Tileset));
    m_tilemap.setTexturePtr(texturePtr);

    // Add the code <-> texture rect.
    m_tilemap.addTextureRect(Tile::TileType::Box_1, sf::IntRect(0 * 32, 0 * 32, 32, 32));

}

Environment::~Environment()
{

}

Tile Environment::getTile(sf::Vector2u index) const
{
    return m_tiles[index.y][index.x];
}

// Sets the tiles data.
void Environment::setTiles(std::vector<std::vector<Tile>>& tiles)
{
    // Sets the tiles.
    m_tiles = tiles;

    // Set the the tilemap data.
    for(unsigned int i(0) ; i < Configuration::TileMapSize.y ; ++i)
    {
        for(unsigned int j(0) ; j < Configuration::TileMapSize.x ; ++j)
        {
            m_tilemap.setTileData(sf::Vector2u(i, j), tiles[i][j].getType());
        }
    }

    // Update the tilemap.
    m_tilemap.update();
}

// Returns the tile containing the position.
sf::Vector2u Environment::getTileIndexContaining(sf::Vector2f pos) const
{
    sf::Vector2i tileIndex(pos.x / Configuration::TilePixelSize.x, pos.y / Configuration::TilePixelSize.y);

    // Make sure the selector is still on the tile map.
    if(tileIndex.x < 0)
        tileIndex.x = 0;
    else if((unsigned int)tileIndex.x >= Configuration::TileMapSize.x)
        tileIndex.x = Configuration::TileMapSize.x - 1;

    if(tileIndex.y < 0)
        tileIndex.y = 0;
    else if((unsigned int)tileIndex.y >= Configuration::TileMapSize.y)
        tileIndex.y = Configuration::TileMapSize.y - 1;

    // Be careful, axes are inverted when speaking of tile indexes.
    return sf::Vector2u(tileIndex.x, tileIndex.y);
}

void Environment::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(m_tilemap, states);
}
