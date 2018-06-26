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
#include "../Chat/Chat.hpp"
#include "../ResourceHolder.hpp"
#include "World.hpp"
#include "../ResourceId.hpp"
#include "../Loading/Loading.hpp"
#include "../Menu/Menu.hpp"
#include "../State.hpp"


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

        // Update
        void update(sf::Time dt);

        // Render
        void render(sf::RenderWindow* window);

        // Event handle
        void EventHandle(sf::Event event);

        // Notification packet
        void notificationPacket(sf::Packet* packet);

    protected:
        // Disconnect to the serveur
        void disconnectToGameServer();

        // Receive all packet of the server
        void receivePacket();

        // Send all input state
        void sendInput();

        // Test all inputs
        void testInput();

        // Receive information packet
        void receiveInformationPacket();

    private:

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

        int ping;

        // World
        World world;

        unsigned long long loosedPacket;

        sf::Time timeOutTimer;

        sf::Time timeOut;

        sf::Time pingTimer;

        sf::Time pingCounter;

        long long pingId;

        State state;

        Menu menu;

        Loading loading;

        sf::RenderWindow* window;

};

#endif // GAME_HPP_INCLUDED
