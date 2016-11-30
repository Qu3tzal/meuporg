#ifndef INFORMATIONSERVER_HPP_INCLUDED
#define INFORMATIONSERVER_HPP_INCLUDED

#include <iostream>
#include <SFML/Network.hpp>
#include "../ServerConfiguration.hpp"
#include "../NetworkValues.hpp"

class Server;

/*
    InformationServer class.
    This class manages the server that answers all the information requests received.
*/
class InformationServer
{
    public:
        // Structure to hold together sockets and timeouts.
        struct Client
        {
            sf::TcpSocket tcpsocket;
            sf::Time timeout;
        };

    public:
        // Constructor.
        InformationServer(Server* gameserver);

        // Destructor.
        virtual ~InformationServer();

        // Inits the server.
        void init();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Updates the server.
        void update(sf::Time dt);

        // Answers the version to the client.
        void answerVersion(Client* client);

        // Answers the number of player to the client.
        void answerNumberOfPlayers(Client* client);

        // Answers the ping request.
        void answerPingRequest(Client* client, int pingId);

    protected:
        // TCP Listener.
        sf::TcpListener m_listener;

        // List of the clients.
        std::vector<Client*> m_clients;

        // Pointer to the server.
        Server* m_gameserver;
};

#endif // INFORMATIONSERVER_HPP_INCLUDED
