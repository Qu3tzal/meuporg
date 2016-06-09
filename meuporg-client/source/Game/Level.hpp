#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>

#include "../ID.hpp"
#include "../Configuration/Configuration.hpp"
#include "../Entity/Entity.hpp"
#include "../Tile/Tile.hpp"

namespace Level
{

    // Reads and loads the level into the playstate.
    bool loadLevelFromFile(std::string filename, Map* levelMap);

}

#endif // LEVEL_HPP
