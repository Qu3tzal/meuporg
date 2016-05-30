#include "Server.hpp"

Server::Server()
    : m_numberOfPlayers(0)
    , m_maximumPlayersCapacity(16)
    , m_loginServer(this)
{

}

Server::~Server()
{
    for(auto accountEntry : m_accounts)
        delete accountEntry.second;
}

void Server::init()
{
    // Init the login server.
    m_loginServer.init();

    // Bind to the game ports.
    m_gameTcpListener.listen(ServerConfiguration::GameTCPPort);
    m_gameUdpSocket.bind(ServerConfiguration::GameUDPPort);
}

bool Server::isRunning() const
{
    return true;
}

void Server::login(sf::Time dt)
{
    m_loginServer.login(dt);

    PendingSocket* pendingSocket = new PendingSocket();
    pendingSocket->tcpSocket = std::make_shared<sf::TcpSocket>();
    pendingSocket->tcpSocket->setBlocking(false);

    if(m_gameTcpListener.accept(*pendingSocket->tcpSocket.get()) == sf::TcpListener::Status::Done)
    {
        // We still don't know to who belongs this socket.
        // We need to wait for the CONNECT packet.
        m_pendingTcpSockets.push_back(pendingSocket);
    }
    else
    {
        delete pendingSocket;
    }

    // Check if we received any CONNECT packet on the pending sockets and update their timeout.
    for(auto pendingSocketItr(m_pendingTcpSockets.begin()) ; pendingSocketItr != m_pendingTcpSockets.end() ;)
    {
        PendingSocket* pendingSocket = (*pendingSocketItr);
        pendingSocket->timeout += dt;

        // Check timeout.
        if(pendingSocket->timeout >= sf::seconds(5.f))
        {
            delete pendingSocket;
            m_pendingTcpSockets.erase(pendingSocketItr);
            continue;
        }

        // Check if received packet.
        sf::Packet packet;
        if(pendingSocket->tcpSocket->receive(packet) == sf::TcpSocket::Status::Done)
        {
            unsigned int networkCode(0);
            packet >> networkCode;

            if(networkCode != NetworkValues::CONNECT)
                continue;

            // Extract username and random token.
            std::string username(""), token("");
            packet >> username >> token;

            // Check if username exists.
            if(m_accounts.find(username) == m_accounts.end())
            {
                // CONNECTION_FAIL_UNKNOWN_USER
                sf::Packet answer;
                answer << NetworkValues::CONNECTION_FAIL_UNKNOWN_USER;
                pendingSocket->tcpSocket->send(answer);

                continue;
            }

            // Check if the username and random token given are the same as ours.
            if(token == m_accounts.at(username)->token)
            {
                // OKAY
                sf::Packet answer;
                answer << NetworkValues::OKAY;
                pendingSocket->tcpSocket->send(answer);

                // Affect the tcp socket to the client.
                m_accounts.at(username)->linkedClient->gameTcp = pendingSocket->tcpSocket;
                m_accounts.at(username)->linkedClient->gameTcpConnected = true;

                // Delete the pending socket.
                delete pendingSocket;
                m_pendingTcpSockets.erase(pendingSocketItr);
                continue;
            }
            else
            {
                // CONNECTION_FAIL_WRONG_TOKEN
                sf::Packet answer;
                answer << NetworkValues::CONNECTION_FAIL_WRONG_TOKEN;
                pendingSocket->tcpSocket->send(answer);
            }
        }

        // Next pending socket.
        pendingSocketItr++;
    }
}

void Server::receiveInput()
{
    // Check if we received any UDP packet.
    sf::Packet packet;
    sf::IpAddress ip;
    short unsigned int port;

    while(m_gameUdpSocket.receive(packet, ip, port) == sf::UdpSocket::Status::Done)
    {
        // Treat the packet.
        // Extract the network code.
        unsigned int networkCode;
        packet >> networkCode;

        // Evaluate the network code.
        switch(networkCode)
        {
            case NetworkValues::CONNECT:
                {
                    // Extract username and token.
                    std::string username(""), token("");
                    packet >> username >> token;

                    // Check if username exists.
                    if(m_accounts.find(username) != m_accounts.end())
                    {
                        // Check if the username and random token given are the same as ours.
                        if(token == m_accounts.at(username)->token)
                        {
                            // OKAY
                            sf::Packet answer;
                            answer << NetworkValues::OKAY;
                            m_accounts.at(username)->linkedClient->gameTcp->send(answer);

                            // Affect the tcp socket to the client.
                            m_accounts.at(username)->linkedClient->ip = ip;
                            m_accounts.at(username)->linkedClient->udpPort = port;
                            m_accounts.at(username)->linkedClient->gameUdpConnected = true;

                            // Replie with the list of the players.
                            answer.clear();

                            answer << getNumberOfPlayers();
                            for(auto accountEntry : m_accounts)
                            {
                                if(accountEntry.second->linkedClient != nullptr)
                                    answer << accountEntry.second->linkedClient->username;
                            }

                            m_accounts.at(username)->linkedClient->gameTcp->send(answer);
                        }
                    }
                }
                break;
            default:
                break;
        }

        // Clear the packet.
        packet.clear();
    }
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

std::vector<Client*>* Server::getClients()
{
    return &m_clients;
}

std::map<std::string, Account*>* Server::getAccounts()
{
    return &m_accounts;
}

void Server::updateNumberOfPlayers()
{
    unsigned int numberOfPlayers(0);

    // Count the number of accounts linked with a connected client.
    std::for_each(m_accounts.begin(), m_accounts.end(), [&numberOfPlayers](std::pair<std::string, Account*> entry){
                        if(entry.second->linkedClient != nullptr)
                            numberOfPlayers++;
                    });

    m_numberOfPlayers = numberOfPlayers;
}
