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
#include <TextureLoader.hpp>

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
        void connectToServer(std::string username);

        // Connects to the gameServer.
        void connectToGameServer(std::string username);

        // Disconnect to the serveur
        void disconnectToGameServer();

        // Receive all packet of the server
        void receivePacket();

        // Send all input state
        void sendInput();

        // Test all inputs
        void testInput();

    private:
        // The version of the client
        const unsigned int Version;

        // Timer for the timeout
        sf::Time timeout;

        // Client is running ?
        bool running;

        // Token
        std::string token;

        // Udp packet nulber
        unsigned long long udpPacketNumber;

        // All tcp Socket
        sf::TcpSocket informationSocket;
        sf::TcpSocket serverSocket;
        sf::TcpSocket gameServerSocket;

        // all udp Socket
        sf::UdpSocket gameServerUdpSocket;

        // PlayerInput
        PlayerInput playerInput;

        // ip of the seveur
        sf::IpAddress ip;

        // TextureLoader
        TextureLoader textures;
};

#endif // GAME_HPP_INCLUDED
