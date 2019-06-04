#include "MapLoader.hpp"
#include "../World/World.hpp"

MapLoader::MapLoader(std::string mapFilepath, World* world)
    : m_mapId(0)
{
    // Perf clock.
    sf::Clock clock;

    // Open file.
    std::ifstream mapfile;
    mapfile.open(mapFilepath.c_str());

    // Read every line.
    std::string line("");
    while(std::getline(mapfile, line))
    {
        std::stringstream ss(line);

        std::string instructionType;
        ss >> instructionType;

        if(instructionType == "entity")
        {
            std::string type;
            ss >> type;

            sf::Vector2f position;
            ss >> position.x;
            ss >> position.y;

            if(type == "box")
                world->createBox(position);
            else if(type == "monster")
                world->createMonster(position);
            else if(type == "tower")
                world->createTower(position);
        }
        else if(instructionType == "id")
        {
            ss >> m_mapId;
        }
        else if(instructionType == "spawn")
        {
            sf::Vector2f position;
            ss >> position.x;
            ss >> position.y;

            world->addSpawnPoint(position);
        }
    }

    // Get loading time.
    m_loadingTime = clock.restart();
}

MapLoader::~MapLoader()
{

}

unsigned int MapLoader::getMapId() const
{
    return m_mapId;
}

sf::Time MapLoader::getLoadingTime() const
{
    return m_loadingTime;
}
