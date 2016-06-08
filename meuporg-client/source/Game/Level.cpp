#include "Level.hpp"

// Level related functions.
namespace Level
{
    bool loadLevelFromFile(std::string filename)
    {
        std::ifstream file(filename);
        std::vector<std::vector<Tile>> tiles;

        if(!file)
            return false;

        unsigned int waste(0);
        file >> waste >> waste;

        // Read tilemap data.
        for(unsigned int i(0) ; i < Configuration::TileMapSize.y ; ++i)
        {
            tiles.push_back(std::vector<Tile>());

            for(unsigned int j(0) ; j < Configuration::TileMapSize.x ; ++j)
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
