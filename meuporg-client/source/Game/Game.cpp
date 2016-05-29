#include "Game.hpp"

Game::Game() : Version(001)
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
    packet << NetworkValues::VERSION;
    socket.send(packet);

    sf::Packet serverVersionPacket;
    socket.receive(serverVersionPacket);

    packet.clear();

    packet << NetworkValues::NUMBER_OF_PLAYERS;
    socket.send(packet);
    sf::Packet playerNumberPacket;
    socket.receive(playerNumberPacket);

    unsigned int serverVersion;
    unsigned int playerNumber;
    unsigned int maximumPlayer;

    serverVersionPacket >> serverVersion;
    playerNumberPacket >> playerNumber >> maximumPlayer;

    std::cout << "Server version : " <<  serverVersion << std::endl <<" Number of player : " << playerNumber << "/" <<  maximumPlayer << std::endl;

    connection:
    packet.clear();
    sf::TcpSocket connectionSocket;
    connectionSocket.connect(ip, 22625);

    std::cout << "---------- Connection en cours ----------" << std::endl;

    packet << NetworkValues::CONNECT << username << Version;
    connectionSocket.send(packet);
    packet.clear();

    connectionSocket.receive(packet);

    unsigned int answer;
    packet >> answer;

    switch(answer)
    {
        case NetworkValues::ACCOUNT_CREATED_RECONNECT :
            std::cout << "Compte crée !" << std::endl << "---------- Connection en cours ----------" << std::endl;
            goto connection;
        break;
        case NetworkValues::CONNECTION_SUCCESS :
            std::cout << "Connection réussi !" << std::endl;
        break;
        case NetworkValues::CONNECTION_FAIL_UNKNOWN_USER :
             std::cout << "Identifiant inconnu !" << std::endl;
        break;
        case NetworkValues::CONNECTION_FAIL_VERSION_ERROR :
            std::cout << "Version invalide !" << std::endl;
        break;
        case NetworkValues::CONNECTION_FAIL_SERVER_FULL :
            std::cout << "Le serveur est complet !" << std::endl;
        break;
        case NetworkValues::CONNECTION_FAIL_UNKNOWN_ERROR :
           std::cout << "Erreur inconnu" << std::endl;
        break;

    }

}

bool Game::isRunning() const
{
    return true;
}

void Game::update(sf::Time dt)
{

}
