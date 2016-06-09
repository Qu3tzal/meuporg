#include "Map.hpp"

Map::Map(kantan::TextureHolder* textures) : tileMap(0, 0)
{
    this->textures = textures;
}

Map::~Map()
{
    //dtor
}

bool Map::loadLevelFromFile(std::string filename)
{
    std::ifstream file(filename);
    std::vector<std::vector<unsigned int>> tiles;

    if(!file)
        return false;

    sf::Vector2f m_size;
    file >> m_size.x >> m_size.y;

    // Read tilemap data.
    for(unsigned int i(0) ; i < m_size.y ; ++i)
    {
        tiles.push_back(std::vector<unsigned int>());

        for(unsigned int j(0) ; j < m_size.x ; ++j)
        {
            unsigned int type(0);
            file >> type;

            tiles[i].push_back(type);
        }
    }
    initTileMap(tiles);


    return true;
}

void Map::createMap()
{
    std::vector<std::vector<unsigned int>> tiles;

    for(unsigned int i(0) ; i <= 768 ; ++i)
    {
        tiles.push_back(std::vector<unsigned int>());

        for(unsigned int j(0) ; j <= 1248 ; j++)
        {
            unsigned int type(0);
            if(i == 0)
            {
                type = 1;
            }
            else if(j == 1248 && i >= 48 && i <= 768)
            {
                type = 1;
            }
            else if(j == 0 && i >= 32 && i <= 768)
            {
                type = 1;
            }
            else
            {
                type = 0;
            }
            tiles[i].push_back(type);
        }
    }

    initTileMap(tiles);


}

void Map::initTileMap(std::vector<std::vector<unsigned int>> tiles)
{
    tileMap = TileMap(m_size.x, m_size.y);

    tileMap.addTextureRect(0, sf::IntRect(0, 0, 32, 32));
    tileMap.addTextureRect(1, sf::IntRect(32, 0, 32, 32));

    tileMap.setTexturePtr(&(textures->get(ResourceId::TILESET)));

    tileMap.setTileData(tiles);

    tileMap.update();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(tileMap, states);
}
