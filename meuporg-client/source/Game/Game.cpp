#include "Game.hpp"

Game::Game() : Version(001), running(true)
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

    std::cout << "Rentrez votre identifiant : ";
    std::cin >> username;

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(ip, 22626, sf::seconds(5.f));
    if (status != sf::Socket::Done)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
        return;
    }

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

    connectToServer(username, ip);
}

void Game::connectToServer(std::string username, sf::IpAddress ip)
{
    sf::Packet packet;
    sf::TcpSocket connectionSocket;
    sf::TcpSocket::Status status = connectionSocket.connect(ip, 22625, sf::seconds(5.f));

    if (status != sf::Socket::Done)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
        return;
    }

    std::cout << "---------- Connexion en cours ----------" << std::endl;

    packet << NetworkValues::CONNECT << username << Version;
    connectionSocket.send(packet);
    packet.clear();

    connectionSocket.receive(packet);

    unsigned int answer;
    packet >> answer;

    switch(answer)
    {
        case NetworkValues::ACCOUNT_CREATED_RECONNECT :
            std::cout << "Compte cree !" << std::endl << "---------- Connexion en cours ----------" << std::endl;

            // Reconnect to the server.
            connectToServer(username, ip);
            break;
        case NetworkValues::CONNECTION_SUCCESS :
            {
                std::cout << "Connexion reussie !" << std::endl;

                std::string token("");
                packet >> token;

                std::cout << "[DEBUG] Token: " << token << std::endl;
            }
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
           std::cout << "Erreur inconnue" << std::endl;
            break;
    }
}

bool Game::isRunning() const
{
    return running;
}

void Game::update(sf::Time dt)
{

}
