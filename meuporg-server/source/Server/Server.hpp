#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <map>

#include <SFML/Network.hpp>

#include "../Accounts.hpp"
#include "../NetworkValues.hpp"
#include "../ServerConfiguration.hpp"
#include "../RandomNumberGenerator/RandomNumberGenerator.hpp"
#include "../LoginServer/LoginServer.hpp"

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

        // Logs in the new players.
        void login(sf::Time dt);

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

        // Returns the list of clients.
        std::vector<Client*>* getClients();

        // Returns the list of accounts.
        std::map<std::string, Account*>* getAccounts();

    protected:
        // Updates the number of players.
        void updateNumberOfPlayers();

    protected:
        // Number of players connected and maximum number of players.
        unsigned int m_numberOfPlayers;
        unsigned int m_maximumPlayersCapacity;

        // List of the clients.
        std::vector<Client*> m_clients;

        // List of the accounts (indexed by the username).
        std::map<std::string, Account*> m_accounts;

        // The login server.
        LoginServer m_loginServer;
};

#endif // SERVER_HPP_INCLUDED
