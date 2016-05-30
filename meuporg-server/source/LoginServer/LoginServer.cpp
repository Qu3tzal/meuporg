#include "LoginServer.hpp"
#include "../Server/Server.hpp"

LoginServer::LoginServer(Server* server)
    : m_server(server)
{
    //ctor
}

LoginServer::~LoginServer()
{
    //dtor
}

void LoginServer::init()
{
    // Listen on the login port.
    m_loginListener.listen(ServerConfiguration::LoginPort);
    m_loginListener.setBlocking(false);
}

void LoginServer::login(sf::Time dt)
{
    // Do not login any body if the server is full.
    if(m_server->getNumberOfPlayers() >= m_server->getMaximumPlayersCapacity())
    {
        sf::TcpSocket tcpsocket;

        // If someone is connected to the login port.
        if(m_loginListener.accept(tcpsocket) == sf::TcpListener::Status::Done)
        {
            sf::Packet packet;
            packet << NetworkValues::CONNECTION_FAIL_SERVER_FULL;

            tcpsocket.send(packet);
            tcpsocket.disconnect();
        }
    }
    else
    {
        Client* tempclient = new Client();
        tempclient->loginTcp.setBlocking(false);

        // If someone connected to the port.
        if(m_loginListener.accept(tempclient->loginTcp) == sf::TcpListener::Status::Done)
        {
            m_clients.push_back(tempclient);
        }
        else
        {
            delete tempclient;
        }

        // Check all pending clients.
        for(auto itr(m_clients.begin()) ; itr != m_clients.end() ;)
        {
            // Alias.
            Client* client = (*itr);

            // Account timeout.
            client->timeout += dt;

            // Check timeout.
            if(client->timeout >= sf::seconds(5.f))
            {
                std::cout << "[LOGIN_SERVER] '" << client->username << "' from (" << client->loginTcp.getRemoteAddress().toString() << ") timed out." << std::endl;

                // Disconnect the account.
                auto accountItr = m_server->getAccounts()->find(client->username);
                (*accountItr).second->linkedClient = nullptr;

                delete client;
                m_clients.erase(itr);
                continue;
            }

            // Check if we received the log in data.
            sf::Packet packet;
            if(client->loginTcp.receive(packet) == sf::TcpSocket::Status::Done)
            {
                // Reset timeout since we received a packet.
                client->timeout = sf::Time::Zero;

                // Decompose packet.
                unsigned int networkCode;
                packet >> networkCode;

                if(networkCode != NetworkValues::CONNECT)
                {
                    std::cout << "[LOGIN_SERVER] Unknown network code : '" << networkCode << "'." << std::endl;
                    itr++;
                    continue;
                }

                packet >> client->username >> client->gameVersion;

                // Check game version.
                if(client->gameVersion != ServerConfiguration::Version)
                {
                    sf::Packet packet;
                    packet << NetworkValues::CONNECTION_FAIL_VERSION_ERROR;
                    client->loginTcp.send(packet);

                    delete client;
                    m_clients.erase(itr);
                    continue;
                }

                // Check if an account is linked to the username.
                auto accountIterator = m_server->getAccounts()->find(client->username);

                if(accountIterator == m_server->getAccounts()->end())
                {
                    /*
                        -> account creation
                        -> send back ACCOUNT_CREATED_RECONNECT
                        -> disconnect login socket
                    */
                    m_accounts[client->username] = new Account();
                    std::cout << "[LOGIN_SERVER] Account '" << client->username << "' created for (" << client->loginTcp.getRemoteAddress().toString() << ")." << std::endl;

                    // Send back ACCOUNT_CREATED_RECONNECT.
                    sf::Packet packet;
                    packet << NetworkValues::ACCOUNT_CREATED_RECONNECT;
                    client->loginTcp.send(packet);

                    delete client;
                    m_clients.erase(itr);
                    continue;
                }
                else
                {
                    /*
                        -> check account->linkedClient == nullptr else CONNECTION_FAIL_ALREADY_CONNECTED
                        -> client->loggedIn = true;
                        -> send back CONNECTION_SUCCESS with a random token
                        -> associate account with random token and client
                    */
                    // Alias.
                    Account* account = (*accountIterator).second;

                    if(account->linkedClient != nullptr)
                    {
                        sf::Packet packet;
                        packet << NetworkValues::CONNECTION_FAIL_ALREADY_CONNECTED;
                        client->loginTcp.send(packet);

                        std::cout << "[LOGIN_SERVER] '" << client->username << "' tried to log in multiple times." << std::endl;

                        delete client;
                        m_clients.erase(itr);
                        continue;
                    }

                    // Mark the client as logged in.
                    client->loggedIn = true;
                    std::cout << "[LOGIN_SERVER] '" << client->username << "' logged in from (" << client->loginTcp.getRemoteAddress().toString() << ")." << std::endl;

                    // Send back CONNECTION_SUCCESS with a random token.
                    // Generate random token.
                    std::stringstream tokenStream("");
                    tokenStream << m_rng.generate() << client->loginTcp.getRemoteAddress().toString() << client->loginTcp.getLocalPort();

                    sf::Packet packet;
                    packet << NetworkValues::CONNECTION_SUCCESS << tokenStream.str();
                    client->loginTcp.send(packet);

                    // Associate account with random token and client.
                    account->token = tokenStream.str();
                    account->linkedClient = client;
                }
            }
            else
            {
                itr++;
            }
        }
    }
}
