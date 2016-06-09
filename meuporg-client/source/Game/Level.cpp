#include "Level.hpp"

// Level related functions.
namespace Level
{
    bool loadLevelFromFile(std::string filename,Map* levelMap)
    {
        std::ifstream file(filename);
        std::vector<std::vector<Tile>> tiles;

        if(!file)
            return false;

        sf::Vector2f size;
        file >> size.x >> size.y;

        // Read tilemap data.
        for(unsigned int i(0) ; i < size.y ; ++i)
        {
            tiles.push_back(std::vector<Tile>());

            for(unsigned int j(0) ; j < size.x ; ++j)
            {
                unsigned int type(0);
                file >> type;

                tiles[i].push_back(Tile(static_cast<Tile::TileType>(type)));
            }
        }
        playstate->setEnvironmentTiles(tiles);


        return true;
    }

}
