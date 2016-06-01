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
    m_gameTcpListener.setBlocking(false);

    m_gameUdpSocket.bind(ServerConfiguration::GameUDPPort);
    m_gameUdpSocket.setBlocking(false);
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
        std::cout << "[GAME_SERVER] New pending socket from (" << pendingSocket->tcpSocket->getRemoteAddress().toString() << ")." << std::endl;
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
        if(pendingSocket->timeout >= ServerConfiguration::PendingSocketTimeout)
        {
            std::cout << "[GAME_SERVER] Pending socket from (" << pendingSocket->tcpSocket->getRemoteAddress().toString() << ") timed out." << std::endl;

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
            {
                std::cout << "[GAME_SERVER] Unknown network code : '" << networkCode << "'." << std::endl;
                continue;
            }

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

                std::cout << "[GAME_SERVER] CONNECTION_FAIL_UNKNOWN_USER from (" << pendingSocket->tcpSocket->getRemoteAddress().toString() << ")." << std::endl;

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

                // Reset timeout.
                m_accounts.at(username)->linkedClient->timeout = sf::Time::Zero;

                std::cout << "[GAME_SERVER] Game TCP connected from (" << pendingSocket->tcpSocket->getRemoteAddress().toString() << ") for '" << username << "'." << std::endl;

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

                std::cout << "[GAME_SERVER] CONNECTION_FAIL_WRONG_TOKEN from (" << pendingSocket->tcpSocket->getRemoteAddress().toString() << ")." << std::endl;
            }
        }

        // Next pending socket.
        pendingSocketItr++;
    }
}

void Server::receiveInput()
{
    receiveInputThroughTCP();
    receiveInputThroughUDP();
}

void Server::update(sf::Time dt)
{
    updateNumberOfPlayers();
    updateTimeoutPlayers(dt);
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

void Server::disconnectPlayer(std::string username, std::string reason)
{
    // Dissociate the account and the client.
    try
    {
        // Find the client associated to the username.
        auto clientItr = std::find_if(m_clients.begin(), m_clients.end(), [username](Client* client){
                                        return client->username == username;
                                    });

        // Alias.
        Client* client = (*clientItr);

        m_accounts.at(username)->linkedClient = nullptr;

        std::cout << "[GAME_SERVER] '" << username << "' has left the game (" << reason << ")." << std::endl;

        // Erase the client.
        delete client;
        m_clients.erase(clientItr);
    }
    catch(std::exception& e)
    {
        std::cerr << "[GAME_SERVER][ERROR] " << e.what() << std::endl;
    }
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

void Server::updateTimeoutPlayers(sf::Time dt)
{
    // Check each client connected to the game server.
    for(auto clientItr(m_clients.begin()) ; clientItr != m_clients.end() ;)
    {
        // Alias.
        Client* client = (*clientItr);

        // Timeout only if in game.
        if(client->ingame)
        {
            // Update timer.
            client->timeout += dt;

            // Check the timeout.
            if(client->timeout >= ServerConfiguration::GameServerTimeout)
            {
                disconnectPlayer(client->username, "timed out");
                continue;
            }
            else
            {
                clientItr++;
            }
        }
        else
        {
            clientItr++;
        }
    }
}

void Server::receiveInputThroughTCP()
{
    // Check if we received any TCP packet.
    for(auto clientItr(m_clients.begin()) ; clientItr != m_clients.end() ;)
    {
        // Alias.
        Client* client = (*clientItr);

        // Timeout only if in game.
        if(client->ingame)
        {
            bool deletedClient(false);

            // Check if we received a packet.
            sf::Packet packet;
            while(client->gameTcp->receive(packet) == sf::TcpSocket::Status::Done)
            {
                // Reset timeout.
                client->timeout = sf::Time::Zero;

                // Extract network code.
                unsigned int networkCode;
                packet >> networkCode;

                switch(networkCode)
                {
                    case NetworkValues::DISCONNECT:
                        // Disconnect the player.
                        disconnectPlayer(client->username, "disconnected");

                        // Notify everyone the player disconnected.
                        notifyPlayerDisconnected(client->username);

                        // Tag we deleted a client.
                        deletedClient = true;
                        break;
                    case NetworkValues::SEND_CHAT_MESSAGE:
                        {
                            // Extract message.
                            std::string message("");
                            packet >> message;

                            std::cout << "[CHAT] " << client->username << ": " << message << std::endl;

                            // Send chat message to everyone.
                            sendChatMessage(client->username, message);
                        }
                        break;
                    default:
                        break;
                }
            }

            // Do not increment if we deleted a client previously.
            if(!deletedClient)
                clientItr++;
        }
        else
        {
            clientItr++;
        }
    }
}

void Server::receiveInputThroughUDP()
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
                        // Ignore packet if client not connected.
                        if(m_accounts.at(username)->linkedClient == nullptr)
                            continue;

                        // Ignore packet if already in game.
                        if(m_accounts.at(username)->linkedClient->ingame)
                            continue;

                        // Check if the username and token given are the same as ours.
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
                            m_accounts.at(username)->linkedClient->ingame = true;

                            // Notify everyone the player connected.
                            notifyPlayerConnected(username);

                            // Reset timeout.
                            m_accounts.at(username)->linkedClient->timeout = sf::Time::Zero;

                            // Replie with the list of the players.
                            answer.clear();

                            answer << getNumberOfPlayers();
                            for(auto accountEntry : m_accounts)
                            {
                                if(accountEntry.second->linkedClient != nullptr)
                                    answer << accountEntry.second->linkedClient->username;
                            }

                            m_accounts.at(username)->linkedClient->gameTcp->send(answer);

                            std::cout << "[GAME_SERVER] Game UDP connected from (" << ip.toString() << ") for '" << username << "'." << std::endl;
                            std::cout << "[GAME_SERVER] '" << username << "' from (" << ip.toString() << ") is now in game !" << std::endl;
                        }
                    }
                }
                break;
            case NetworkValues::INPUT:
                {
                    // Extract username and token.
                    std::string username(""), token("");
                    packet >> username >> token;

                    // Check if username exists.
                    if(m_accounts.find(username) != m_accounts.end())
                    {
                        // Ignore packet if client not connected.
                        if(m_accounts.at(username)->linkedClient == nullptr)
                            continue;

                        // Ignore packet if not already in game.
                        if(!m_accounts.at(username)->linkedClient->ingame)
                            continue;

                        // Check if the username and token given are the same as ours.
                        if(token == m_accounts.at(username)->token)
                        {
                            // Alias.
                            Client* client = m_accounts.at(username)->linkedClient;

                            // Reset timeout.
                            m_accounts.at(username)->linkedClient->timeout = sf::Time::Zero;

                            // Extract udp packet id.
                            unsigned long long udpPacketId(0);
                            packet >> udpPacketId;

                            // Skip packet if we already received newer inputs.
                            if(udpPacketId < client->lastPacketIdReceived)
                                break;

                            // Update the last packet id.
                            client->lastPacketIdReceived = udpPacketId;

                            // Extract client input.
                            packet  >> client->inputs.isMoveUpKeyPressed
                                    >> client->inputs.isMoveDownKeyPressed
                                    >> client->inputs.isMoveLeftKeyPressed
                                    >> client->inputs.isMoveRightKeyPressed;
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

void Server::sendChatMessage(std::string username, std::string message)
{
    // Record the message.
    m_chatLog.push_back(std::pair<std::string, std::string>(username, message));

    // Prepare the packet.
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::RECEIVE_CHAT_MESSAGE << username << message;

    // Send the message to all the in-game clients.
    for(Client* client : m_clients)
    {
        if(client->ingame)
            client->gameTcp->send(packet);
    }
}

void Server::notifyPlayerConnected(std::string username)
{
    // Prepare the packet.
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::PLAYER_CONNECTED << username;

    // Send the notification to all the in-game clients.
    for(Client* client : m_clients)
    {
        if(client->ingame)
            client->gameTcp->send(packet);
    }
}

void Server::notifyPlayerDisconnected(std::string username)
{
    // Prepare the packet.
    sf::Packet packet;
    packet << NetworkValues::NOTIFY << NetworkValues::PLAYER_DISCONNECTED << username;

    // Send the notification to all the in-game clients.
    for(Client* client : m_clients)
    {
        if(client->ingame)
            client->gameTcp->send(packet);
    }
}
