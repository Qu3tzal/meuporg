#ifndef ACCOUNTS_HPP_INCLUDED
#define ACCOUNTS_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <memory>

#include "PlayerInput.hpp"

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
    bool ingame = false;
    unsigned int currentWorld = 0;

    unsigned int gameVersion = 0;
    std::string username = "";

    PlayerInput inputs = {false, false, false, false};
    unsigned long long lastPacketIdReceived = 0;
    unsigned long long lastPacketIdSent = 0;
    unsigned int lostPackets = 0;
};

// Account structure.
struct Account
{
    Client* linkedClient = nullptr;
    std::string token = "";
};

#endif // ACCOUNTS_HPP_INCLUDED
