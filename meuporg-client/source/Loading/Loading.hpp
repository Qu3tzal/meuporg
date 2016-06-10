#ifndef LOADING_HPP
#define LOADING_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../ResourceHolder.hpp"
#include "GUITextInputPool.hpp"
#include "GUIButtonPool.hpp"
#include "../ResourceId.hpp"
#include "../Game/Game.hpp"

class Loading : public sf::Drawable, sf::Transformable
{
    public:
        Loading(sf::TcpSocket* informationSocket, sf::TcpSocket* serverSocket, sf::TcpSocket* gameServerSocket, sf::UdpSocket* gameServerUdpSocket, kantan::FontHolder* fonts, sf::RenderWindow* window, Game::State* state);
        virtual ~Loading();

        // Establish the communication with the server.
        void serverConnection();

        void init();

        void update(sf::Time dt);

        void eventHandle(sf::Event e);

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
        std::string username;

        GUIButtonPool buttons;

        GUITextInputPool textInputs;

        Game::State* state;


    private:
};

#endif // LOADING_HPP
