#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include <SFML/System.hpp>

/*
    World class.
    Manages the world for a single unit.
*/
class World
{
    public:
        // Ctor.
        World();

        // Dtor.
        virtual ~World();

        // Initializes the world.
        void init();

        // Updates the world.
        void update(sf::Time dt);

    protected:
};

#endif // WORLD_HPP_INCLUDED
