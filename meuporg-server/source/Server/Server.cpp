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

}

bool Server::isRunning() const
{
    return true;
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
