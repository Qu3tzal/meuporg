#ifndef LOADING_HPP
#define LOADING_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../ResourceHolder.hpp"
#include "GUITextInputPool.hpp"
#include "GUIButtonPool.hpp"
#include "../ResourceId.hpp"
#include "../State.hpp"
#include <iostream>
#include <functional>
#include "../NetworkValues.hpp"

class Loading : public sf::Drawable, sf::Transformable
{
    public:
        Loading(sf::TcpSocket* informationSocket, sf::TcpSocket* serverSocket, sf::TcpSocket* gameServerSocket, sf::UdpSocket* gameServerUdpSocket, kantan::FontHolder* fonts, sf::RenderWindow* window, State* state, std::string* token, std::string* username);
        virtual ~Loading();

        // Establish the communication with the server.
        void serverConnection();

        void init();

        void update(sf::Time dt);

        void eventHandle(sf::Event e);

        void nextStep();

    protected:

         // All tcp Socket
        sf::TcpSocket* informationSocket;
        sf::TcpSocket* serverSocket;
        sf::TcpSocket* gameServerSocket;

        // all udp Socket
        sf::UdpSocket* gameServerUdpSocket;

        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

         // Connects to the server.
        void connectToServer();

        // Connects to the gameServer.
        void connectToGameServer();

        // ip of the seveur
        sf::IpAddress ip;

        // Username
        std::string* username;

        std::string* token;

        GUIButtonPool buttons;

        GUITextInputPool textInputs;

        State* state;

        kantan::FontHolder* fonts;

        sf::Text text;

        bool showText;


    private:

        // The version of the client
        const unsigned int Version;
};

#endif // LOADING_HPP
