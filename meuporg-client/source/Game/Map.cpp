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

void Map::createMap(int mapId)
{
    switch(mapId)
    {
    case 0:
        {
            std::vector<std::vector<unsigned int>> tiles;
            m_size = sf::Vector2f(40, 25);

            for(unsigned int i(0) ; i <= m_size.y ; i++)
            {
                tiles.push_back(std::vector<unsigned int>());

                for(unsigned int j(0) ; j <= m_size.x ; j++)
                {
                    unsigned int type(0);
                    if(i == 0)
                    {
                        type = 1;
                    }
                    else if(j == 39 && i >= 0 && i <= 24)
                    {
                        type = 1;
                    }
                    else if(j == 0 && i >= 0 && i <= 24)
                    {
                        type = 1;
                    }
                    else if(i == 24)
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
        break;
    default:
        break;
    }

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
