#include "Server.hpp"

Server::Server()
    : m_numberOfPlayers(0)
    , m_maximumPlayersCapacity(16)
    , m_loginServer(this)
{

}

Server::~Server()
{
    for(auto pair : m_accounts)
        delete pair.second;
}

void Server::init()
{
    m_loginServer.init();
}

bool Server::isRunning() const
{
    return true;
}

void Server::login(sf::Time dt)
{
    m_loginServer.login(dt);
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
