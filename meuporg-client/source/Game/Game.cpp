#include "Game.hpp"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::init()
{
    serverConnection();
}

void Game::serverConnection()
{
    sf::IpAddress ip;
    std::string username;

    std::cout << "Rentrez l'ip du serveur : ";
    std::cin >> ip;

    std::cout << "Rentrez votre indentifiant : ";
    std::cin >> username;

    sf::TcpSocket socket;
    socket.connect(ip, 22626);

    sf::Packet packet;
    packet << NetworkValue::VERSION;

    socket.send(packet);

    sf::Packet serverVersionPacket;

    socket.receive(serverVersionPacket);

    packet.clear();

    packet << NetworkValue::NUMBER_OF_PLAYERS;

    socket.send(packet);

    sf::Packet playerNumberPacket;

    socket.receive(playerNumberPacket);

    std::string serverVersion;
    std::string playerNumber;
    std::string maximumPlayer;

    serverVersionPacket >> serverVersion;
    playerNumberPacket >> playerNumber >> maximumPlayer;

    std::cout << "Server version :" <<  serverVersion << "Number of player : " << playerNumber + "/" +  maximumPlayer<< std::endl;
}

bool Game::isRunning() const
{
    return true;
}

void Game::update(sf::Time dt)
{

}
