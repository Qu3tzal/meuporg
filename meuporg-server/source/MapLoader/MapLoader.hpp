#ifndef MAPLOADER_HPP_INCLUDED
#define MAPLOADER_HPP_INCLUDED

#include <iostream>
#include <fstream>

#include <SFML/System.hpp>

class World;

/*
    MapLoader class.
    Loads a map into a world.
*/
class MapLoader
{
    public:
        // Ctor.
        MapLoader(std::string mapFilepath, World* world);

        // Dtor.
        virtual ~MapLoader();

        // Returns the map id.
		unsigned int getMapId() const;

        // Returns the time it took to load the map.
        sf::Time getLoadingTime() const;

    protected:
        // Map id.
        unsigned int m_mapId;

        // Loading time.
        sf::Time m_loadingTime;
};

#endif // MAPLOADER_HPP_INCLUDED
