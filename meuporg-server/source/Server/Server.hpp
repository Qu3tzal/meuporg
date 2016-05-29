#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../ServerConfiguration.hpp"

/*
    Server class.
    This class manages the main functions of the server.
*/
class Server
{
    public:
        // Constructor.
        Server();

        // Destructor.
        virtual ~Server();

        // Inits the server.
        void init();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Receives the input from the clients.
        void receiveInput();

        // Updates the server.
        void update(sf::Time dt);

        // Sends the update to the clients.
        void sendUpdate();

        // Returns the number of players currently online.
        unsigned int getNumberOfPlayers() const;

        // Return the maximum players capacity of the server.
        unsigned int getMaximumPlayersCapacity() const;

    protected:
        unsigned int m_numberOfPlayers;
        unsigned int m_maximumPlayersCapacity;
};

#endif // SERVER_HPP_INCLUDED
