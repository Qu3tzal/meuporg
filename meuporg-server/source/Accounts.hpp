#ifndef ACCOUNTS_HPP_INCLUDED
#define ACCOUNTS_HPP_INCLUDED

#include <SFML/Network.hpp>

// Client structure.
struct Client
{
    sf::TcpSocket loginTcp;
    sf::TcpSocket gameTcp;
    sf::UdpSocket gameUdp;
    sf::Time timeout = sf::Time::Zero;

    bool loggedIn = false;

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
