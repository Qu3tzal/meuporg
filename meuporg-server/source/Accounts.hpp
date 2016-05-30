#ifndef ACCOUNTS_HPP_INCLUDED
#define ACCOUNTS_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <memory>

// Client structure.
struct Client
{
    sf::TcpSocket loginTcp;
    std::shared_ptr<sf::TcpSocket> gameTcp;

    sf::IpAddress ip;
    unsigned int udpPort;

    sf::Time timeout = sf::Time::Zero;

    bool loggedIn = false;
    bool gameTcpConnected = false;
    bool gameUdpConnected = false;

    unsigned int gameVersion = 0;
    std::string username = "";
};

// Account structure.
struct Account
{
    Client* linkedClient = nullptr;
    std::string token = "";
};

#endif // ACCOUNTS_HPP_INCLUDED
