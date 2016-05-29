#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <../NetworkValues.hpp>
#include <../PlayerInput.hpp>

class Game
{
    public:

        // Constructor
        Game();

        // Destructor
        virtual ~Game();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Initialisation
        void init();

        // Connect to the server
        void serverConnection();
        // Update
        void update(sf::Time dt);

    protected:

    private:
        const unsigned int Version;
        sf::Time timeout;
        bool running;
};

#endif // GAME_HPP_INCLUDED
