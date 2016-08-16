#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <fstream>
#include <sstream>

#include "TileMap.hpp"
#include "Tile.hpp"
#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"

class Map : public sf::Drawable, sf::Transformable
{
    public:
        Map(kantan::TextureHolder* textures);
        virtual ~Map();

        bool loadLevelFromFile(std::string path);

        void initTileMap(std::vector<std::vector<unsigned int>> tiles);

        void createMap(int mapId);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        sf::Vector2f m_size;

        TileMap tileMap;

        kantan::TextureHolder* textures;

    private:
};

#endif // MAP_HPP
