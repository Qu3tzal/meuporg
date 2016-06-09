#include "Tile.hpp"

std::map<std::string, Tile::TileType> TILE_TYPE_DESCRIPTION_MAP =
{
    {"Box_1", Tile::TileType::Box_1},
    {"Grass", Tile::TileType::GRASS}

};

std::string Tile::getTileDescription(TileType type)
{
    for(auto itr(TILE_TYPE_DESCRIPTION_MAP.begin()) ; itr != TILE_TYPE_DESCRIPTION_MAP.end() ; ++itr)
        if(itr->second == type)
            return itr->first;

    return "";
}

Tile::TileType Tile::getTileType(std::string description)
{
    for(auto itr(TILE_TYPE_DESCRIPTION_MAP.begin()) ; itr != TILE_TYPE_DESCRIPTION_MAP.end() ; ++itr)
        if(itr->first == description)
            return itr->second;

    return Tile::TileType::None;
}

Tile::Tile(Tile::TileType type)
    : m_type(type)
{
}

Tile::~Tile()
{
}

Tile::TileType Tile::getType() const
{
    return m_type;
}


