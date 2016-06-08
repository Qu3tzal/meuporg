#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>

#include "../NetworkValues.hpp"
#include "../PlayerInput.hpp"
#include "../RandomNumberGenerator/RandomNumberGenerator.hpp"
#include "TextureLoader.hpp"
#include "Chat.hpp"
#include "../ResourceHolder.hpp"
#include "World.hpp"
#include "../ResourceId.hpp"

class Game
{
    public:

        // Constructor
        Game(sf::RenderWindow* window);

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
        void render(sf::RenderWindow* window);

        // Event handle
        void EventHandle(sf::Event event);

        // Notification packet
        void notificationPacket(sf::Packet* packet);

    protected:
        // Connects to the server.
        void connectToServer();

        // Connects to the gameServer.
        void connectToGameServer();

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

        unsigned long long udpPacketNumberReceive;

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

        // Username
        std::string username;

        // Chat
        Chat chat;

        // TextureHolder
        kantan::TextureHolder textures;

        // FontHolder
        kantan::FontHolder fonts;

        // World
        World world;

        unsigned long long loosedPacket;

        sf::Time timeOutTimer;

        sf::Time timeOut;
};

#endif // GAME_HPP_INCLUDED
