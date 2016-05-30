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

    sf::Socket::Status status = informationSocket.connect(ip, 22626, sf::seconds(5.f));
    if (status != sf::Socket::Done)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
        return;
    }

    sf::Packet packet;
    packet << NetworkValues::VERSION;
    informationSocket.send(packet);

    sf::Packet serverVersionPacket;
    informationSocket.receive(serverVersionPacket);

    packet.clear();

    packet << NetworkValues::NUMBER_OF_PLAYERS;
    informationSocket.send(packet);
    sf::Packet playerNumberPacket;
    informationSocket.receive(playerNumberPacket);

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
    sf::TcpSocket::Status status = serverSocket.connect(ip, 22625, sf::seconds(5.f));

    if (status != sf::Socket::Done)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
        return;
    }

    std::cout << "---------- Connexion en cours ----------" << std::endl;

    packet << NetworkValues::CONNECT << username << Version;
    serverSocket.send(packet);
    packet.clear();

    serverSocket.receive(packet);

    unsigned int answer;
    packet >> answer;
    std::cout << answer << std::endl;
    switch(answer)
    {
        case NetworkValues::ACCOUNT_CREATED_RECONNECT :
            std::cout << "---------- Creation du compte ----------" << std::endl;
            serverSocket.disconnect();

            // Reconnect to the server.
            connectToServer(username, ip);
            break;
        case NetworkValues::CONNECTION_SUCCESS :
            {
                std::cout << "Connexion reussie !" << std::endl;

                std::string token("");
                packet >> token;

                std::cout << "[DEBUG] Token: " << token << std::endl;
                connectToGameServer(username, ip, token);
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
        case NetworkValues::CONNECTION_FAIL_ALREADY_CONNECTED :
            std::cout << "Vous etes deja connecte(e)" << std::endl;
            break;
    }
}

void Game::connectToGameServer(std::string username, sf::IpAddress ip, std::string token)
{
    std::cout << "---------- Attente de reponse du serveur ----------" << std::endl;
    sf::TcpSocket::Status status = gameServerSocket.connect(ip, 22624, sf::seconds(5.f));

    if (status != sf::Socket::Done)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
        return;
    }
    std::cout << "---------- Connexion en cours ----------" << std::endl;
    sf::Packet packet;
    packet << NetworkValues::CONNECT << username << token;

    gameServerSocket.send(packet);
    packet.clear();
    gameServerSocket.receive(packet);

    unsigned int answer;
    packet >> answer;

    if(answer == NetworkValues::OKAY)
    {
        packet.clear();
        packet << NetworkValues::CONNECT <<username << token;

        sf::UdpSocket::Status status;
        gameServerUdpSocket.setBlocking(false);

        while(status != sf::Socket::Done)
        {
             status = gameServerUdpSocket.send(packet, ip, 22623);
        }

        packet.clear();
        gameServerSocket.receive(packet);

        packet >> answer;

        if(answer == NetworkValues::OKAY)
        {
            std::cout << "---------- Connexion reussi ----------" << std::endl;
            packet.clear();
            gameServerSocket.receive(packet);
            int playerNumber = 0;
            packet >> playerNumber;

            //std::vector<std::string> listOfPlayer;
            std::cout << "Liste des joueurs : " << std::endl;
            for(int i = 0 ; i < playerNumber ; i++)
            {
                std::string playerName = "";
                packet >> playerName;
                std::cout << "\t" << "[" << i << "] " << playerName << std::endl;
                //std::string playerName = "";
                //packet >> playerName;
                //listOfPlayer.push_back(playerName);
            }
        }
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_WRONG_TOKEN)
    {
        std::cout << "Token invalide " << std::endl;
        gameServerSocket.disconnect();
        connectToGameServer(username, ip, token);
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_UNKNOWN_USER)
    {
        std::cout << "Nom inconnu" << std::endl;
        gameServerSocket.disconnect();
        connectToGameServer(username, ip, token);
    }

}

bool Game::isRunning() const
{
    return running;
}

void Game::update(sf::Time dt)
{

}

void Game::render(sf::RenderWindow& window)
{
    window.clear(sf::Color::White);

    window.display();
}
