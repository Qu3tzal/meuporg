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
    sf::Uint64 udpPort;

    sf::Time timeout = sf::Time::Zero;

    bool loggedIn = false;
    bool gameTcpConnected = false;
    bool gameUdpConnected = false;
    bool ingame = false;
    int currentWorld = -1;

    sf::Uint64 gameVersion = 0;
    std::string username = "";

    PlayerInput inputs = {false, false, false, false};
    sf::Uint64 lastPacketIdReceived = 0;
    sf::Uint64 lastPacketIdSent = 0;
    sf::Uint64 lostPackets = 0;
};

// Account structure.
struct Account
{
    Client* linkedClient = nullptr;
    std::string token = "";
};

#endif // ACCOUNTS_HPP_INCLUDED
