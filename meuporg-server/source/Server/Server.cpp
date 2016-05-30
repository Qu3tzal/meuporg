#include "Server.hpp"

Server::Server()
    : m_numberOfPlayers(0)
    , m_maximumPlayersCapacity(16)
{

}

Server::~Server()
{
    for(auto pair : m_accounts)
        delete pair.second;
}

void Server::init()
{
    // Listen on the login port.
    m_loginListener.listen(ServerConfiguration::LoginPort);
    m_loginListener.setBlocking(false);
}

bool Server::isRunning() const
{
    return true;
}

void Server::login(sf::Time dt)
{
    // Do not login any body if the server is full.
    if(m_numberOfPlayers >= m_maximumPlayersCapacity)
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
                auto accountItr = m_accounts.find(client->username);
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
                auto accountIterator = m_accounts.find(client->username);

                if(accountIterator == m_accounts.end())
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

void Server::receiveInput()
{

}

void Server::update(sf::Time dt)
{
    updateNumberOfPlayers();
}

void Server::sendUpdate()
{

}

unsigned int Server::getNumberOfPlayers() const
{
    return m_numberOfPlayers;
}

unsigned int Server::getMaximumPlayersCapacity() const
{
    return m_maximumPlayersCapacity;
}

void Server::updateNumberOfPlayers()
{
    unsigned int numberOfPlayers(0);

    // Count the number of accounts linked with a connected client.
    std::for_each(m_accounts.begin(), m_accounts.end(), [&numberOfPlayers](std::pair<std::string, Account*> entry){
                        if(entry.second->linkedClient == nullptr)
                            numberOfPlayers++;
                    });

    m_numberOfPlayers = numberOfPlayers;
}
