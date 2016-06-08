#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

/*
    Tile class.
    Simple way to encapsulate data relative to one tile.
*/
class Tile
{
    public:
        enum TileType
        {
            Box_1,
            GRASS,

            None
        };

        static std::string getTileDescription(TileType type);

        static TileType getTileType(std::string description);

    public:
        // Constructor.
        Tile(TileType type = TileType::SandGround_0);

        // Destructor.
        virtual ~Tile();

        // Returns the type of the tile.
        TileType getType() const;

        // Returns true if it is crossable.
        bool isCrossable() const;

    protected:
        // The type of the tile.
        TileType m_type;
};

#endif // TILE_HPP
