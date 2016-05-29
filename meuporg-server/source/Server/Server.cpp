#include "Server.hpp"

Server::Server()
    : m_numberOfPlayers(0)
    , m_maximumPlayersCapacity(16)
{

}

Server::~Server()
{

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
                std::cout << "[LOGIN_SERVER] '" << client->name << "' from (" << client->loginTcp.getRemoteAddress().toString() << ") timed out." << std::endl;
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

                packet >> client->name >> client->gameVersion;

                // Check game version.
                if(client->gameVersion != ServerConfiguration::Version)
                {
                    sf::Packet packet;
                    packet << NetworkValues::CONNECTION_FAIL_VERSION_ERROR;
                    client->loginTcp.send(packet);

                    delete client;
                    continue;
                }

                // Check if an account is linked to the username.
                /*
                    Check in accounts if username exists.
                    If not:
                        -> account creation
                        -> send back ACCOUNT_CREATED_RECONNECT
                        -> disconnect login socket
                    Else:
                        -> client->loggedIn = true;
                        -> client->accountId = the account id
                        -> send back CONNECTION_SUCCESS with a random token
                        -> associate account with random token
                */

                client->loggedIn = true;

                std::cout << "[LOGIN_SERVER] '" << client->name << "' logged in from (" << client->loginTcp.getRemoteAddress().toString() << ")." << std::endl;

                // Answer connection success.
                sf::Packet packet;
                packet << NetworkValues::CONNECTION_SUCCESS;
                client->loginTcp.send(packet);
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
