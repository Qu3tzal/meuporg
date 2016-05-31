#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <../NetworkValues.hpp>
#include <../PlayerInput.hpp>
#include <SFML/Graphics.hpp>
#include <../RandomNumberGenerator/RandomNumberGenerator.hpp>
#include <sstream>

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

        // Establish the communication with the server.
        void serverConnection();

        // Update
        void update(sf::Time dt);

        // Render
        void render(sf::RenderWindow& window);

        // Event handle
        void EventHandle(sf::Event event);

    protected:
        // Connects to the server.
        void connectToServer(std::string username, sf::IpAddress ip);

        // Connects to the gameServer.
        void connectToGameServer(std::string username, sf::IpAddress ip, std::string token);

        // Disconnect to the serveur
        void disconnectToGameServer();

    private:
        // The version of the client
        const unsigned int Version;

        // Timer for the timeout
        sf::Time timeout;

        // Client is running ?
        bool running;

        // All tcp Socket
        sf::TcpSocket informationSocket;
        sf::TcpSocket serverSocket;
        sf::TcpSocket gameServerSocket;

        // all udp Socket
        sf::UdpSocket gameServerUdpSocket;
};

#endif // GAME_HPP_INCLUDED
