#include "Loading.hpp"

Loading::Loading(sf::TcpSocket* informationSocket, sf::TcpSocket* serverSocket, sf::TcpSocket* gameServerSocket, sf::UdpSocket* gameServerUdpSocket, kantan::FontHolder* fonts, sf::RenderWindow* window, Game::State* state) :
    textInputs(window, fonts)
    , buttons(window, fonts)
{
    this->informationSocket = informationSocket;
    this->serverSocket = serverSocket;
    this->gameServerSocket = gameServerSocket;
    this->gameServerUdpSocket = gameServerUdpSocket;
    this->state = state;
}

Loading::~Loading()
{
    //dtor
}

void Loading::init()
{

}

void Loading::update(sf::Time dt)
{

}

void Loading::eventHandle(sf::Event e)
{

}

void Loading::serverConnection()
{

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

    connectToServer();
}

void Loading::connectToServer()
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
    switch(answer)
    {
        case NetworkValues::ACCOUNT_CREATED_RECONNECT :
            std::cout << "---------- Creation du compte ----------" << std::endl;
            serverSocket.disconnect();

            // Reconnect to the server.
            connectToServer();
            break;
        case NetworkValues::CONNECTION_SUCCESS :
            {
                std::cout << "Connexion reussie !" << std::endl;

                packet >> token;

                std::cout << "[DEBUG] Token: " << token << std::endl;
                connectToGameServer();
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

void Loading::connectToGameServer()
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
        packet << NetworkValues::CONNECT << username << token;

        gameServerSocket.setBlocking(false);
        gameServerUdpSocket.setBlocking(false);

        sf::Packet receivePacket;

        // While we didn't received anything, we keep sending on UDP.
        sf::Clock clock;
        while(gameServerSocket.receive(receivePacket) != sf::Socket::Done)
        {
            if(clock.getElapsedTime() >= sf::seconds(0.5f))
            {
                gameServerUdpSocket.send(packet, ip, 22623);
                clock.restart();
            }
        }

        gameServerSocket.setBlocking(true);

        receivePacket >> answer;

        if(answer == NetworkValues::OKAY)
        {
            std::cout << "---------- Connexion reussi ----------" << std::endl;
            receivePacket.clear();
            gameServerSocket.receive(receivePacket);
            gameServerSocket.setBlocking(false);
            gameServerUdpSocket.setBlocking(false);
            int playerNumber = 0;
            receivePacket >> playerNumber;
            state = State::JEU;

            std::cout << "Liste des joueurs : " << std::endl;
            for(int i = 1 ; i <= playerNumber ; i++)
            {
                std::string playerName = "";
                receivePacket >> playerName;
                std::cout << "\t" << "[" << i << "] " << playerName << std::endl;
            }
        }
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_WRONG_TOKEN)
    {
        std::cout << "Token invalide " << std::endl;
        gameServerSocket.disconnect();
        connectToGameServer();
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_UNKNOWN_USER)
    {
        std::cout << "Nom inconnu" << std::endl;
        gameServerSocket.disconnect();
        connectToGameServer();
    }

}

void Loading::draw(sf::RenderTarget& window, sf::RenderStates states) const
{

    window.draw(textInputs);
    window.draw(buttons);

}
