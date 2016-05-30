#ifndef LOGINSERVER_HPP_INCLUDED
#define LOGINSERVER_HPP_INCLUDED

#include "../Accounts.hpp"
#include "../RandomNumberGenerator/RandomNumberGenerator.hpp"

class Server;

/*
    LoginServer class.
    This class manages all the connection/registration of clients.
*/
class LoginServer
{
    public:
        // Ctor.
        LoginServer(Server* server);

        // Dtor.
        virtual ~LoginServer();

        // Inits the login server.
        void init();

        // Logs in the new players.
        void login(sf::Time dt);

    protected:
        // Pointer to the server.
        Server* m_server;

        // Login TCP listener.
        sf::TcpListener m_loginListener;

        // List of the clients.
        std::vector<Client*> m_clients;

        // List of the accounts (indexed by the username).
        std::map<std::string, Account*> m_accounts;

        // Random number generator.
        RandomNumberGenerator m_rng;
};

#endif // LOGINSERVER_HPP_INCLUDED
