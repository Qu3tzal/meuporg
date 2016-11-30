#include "InformationServer.hpp"
#include "../Server/Server.hpp"

InformationServer::InformationServer(Server* gameserver)
    : m_gameserver(gameserver)
{

}

InformationServer::~InformationServer()
{
    // Clear memory.
    for(Client* client : m_clients)
        delete client;

    // Release network.
    m_listener.close();
}

void InformationServer::init()
{
    m_listener.listen(ServerConfiguration::InformationPort);
    m_listener.setBlocking(false);
}

bool InformationServer::isRunning() const
{
    return true;
}

void InformationServer::update(sf::Time dt)
{
    Client* client = new Client();

    // Check if we can accept a new socket.
    if(m_listener.accept(client->tcpsocket) == sf::TcpListener::Status::Done)
    {
        std::cout << "[INFORMATION_SERVER] Accepted new client (" << client->tcpsocket.getRemoteAddress().toString() << ")." << std::endl;
        m_clients.push_back(client);

        client->tcpsocket.setBlocking(false);
        client->timeout = sf::Time::Zero;
    }
    else
    {
        delete client;
    }

    // Check if we received anything from any socket.
    for(auto itr(m_clients.begin()) ; itr != m_clients.end() ;)
    {
        // Alias.
        Client* client = (*itr);

        // Timeout.
        client->timeout += dt;

        // If the client timed out, we delete it.
        if(client->timeout >= ServerConfiguration::InformationServerTimeout)
        {
            std::cout << "[INFORMATION_SERVER] Client timed out (" << client->tcpsocket.getRemoteAddress().toString() << ")." << std::endl;
            delete client;
            m_clients.erase(itr);
            continue;
        }
        else
        {
            // Check if we received anything.
            sf::Packet packet;
            if(client->tcpsocket.receive(packet) == sf::TcpSocket::Status::Done)
            {
                // Extract the network code.
                unsigned int networkcode;
                packet >> networkcode;

                // Analyse it.
                switch(networkcode)
                {
                    case NetworkValues::VERSION:
                        answerVersion(client);
                        std::cout << "[INFORMATION_SERVER] Version sent to client (" << client->tcpsocket.getRemoteAddress().toString() << ")." << std::endl;
                        break;
                    case NetworkValues::NUMBER_OF_PLAYERS:
                        answerNumberOfPlayers(client);
                        std::cout << "[INFORMATION_SERVER] Number of players sent to client (" << client->tcpsocket.getRemoteAddress().toString() << ")." << std::endl;
                        break;
                    case NetworkValues::PING:
                        {
                            int pingId(0);
                            packet >> pingId;
                            answerPingRequest(client, pingId);
                            std::cout << "[INFORMATION_SERVER] Ping answered to client (" << client->tcpsocket.getRemoteAddress().toString() << ")." << std::endl;
                        }
                        break;
                    default:
                        break;
                }
            }

            itr++;
        }
    }
}

void InformationServer::answerVersion(Client* client)
{
    // Prepare the packet.
    sf::Packet packet;
    packet << ServerConfiguration::Version;

    // Send it.
    //client->tcpsocket.setBlocking(true);
    client->tcpsocket.send(packet);
    //client->tcpsocket.setBlocking(false);
}

void InformationServer::answerNumberOfPlayers(Client* client)
{
    // Prepare the packet.
    sf::Packet packet;
    packet << m_gameserver->getNumberOfPlayers() << m_gameserver->getMaximumPlayersCapacity();

    // Send it.
    //client->tcpsocket.setBlocking(true);
    client->tcpsocket.send(packet);
    //client->tcpsocket.setBlocking(false);
}

void InformationServer::answerPingRequest(Client* client, int pingId)
{
    // Prepare the packet.
    sf::Packet packet;
    packet << NetworkValues::PING << pingId;

    // Send it.
    //client->tcpsocket.setBlocking(true);
    client->tcpsocket.send(packet);
    //client->tcpsocket.setBlocking(false);
}
