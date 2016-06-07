#include "Game.hpp"

Game::Game(sf::RenderWindow* window) : Version(001)
    , running(true)
    , token("")
    , udpPacketNumber(0)
    , udpPacketNumberReceive(0)
    , username("")
    , chat(window, &gameServerSocket, &fonts)
    , world(&textures, &fonts)
{
    //ctor
    fonts.load(1, "assets/fonts/secrcode.ttf");
    textures.load(1, "assets/saitama_spritesheet.png");
}

Game::~Game()
{
    //dtor
    disconnectToGameServer();
}

void Game::init()
{
    chat.init();
    serverConnection();
    world.init();
}

void Game::serverConnection()
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

void Game::connectToServer()
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

void Game::connectToGameServer()
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
        while(gameServerSocket.receive(receivePacket) != sf::Socket::Done)
        {
            gameServerUdpSocket.send(packet, ip, 22623);
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

            //std::vector<std::string> listOfPlayer;
            std::cout << "Liste des joueurs : " << std::endl;
            for(int i = 1 ; i <= playerNumber ; i++)
            {
                std::string playerName = "";
                receivePacket >> playerName;
                std::cout << "\t" << "[" << i << "] " << playerName << std::endl;
                //std::string playerName = "";
                //receivePacket >> playerName;
                //listOfPlayer.push_back(playerName);
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

void Game::disconnectToGameServer()
{
    sf::Packet packet;
    packet << NetworkValues::DISCONNECT;
    gameServerSocket.send(packet);
}

bool Game::isRunning() const
{
    return running;
}

void Game::update(sf::Time dt)
{
    if(!chat.isActive())
        testInput();
    sendInput();
    receivePacket();
    chat.update();
    world.update(dt);
}

void Game::EventHandle(sf::Event event)
{
    chat.handleEvent(event);
}

void Game::receivePacket()
{
    sf::Packet packet;
    sf::Socket::Status status = gameServerSocket.receive(packet);

    if(status == sf::Socket::Status::Done)
    {
        unsigned int netCode(0);
        packet >> netCode;

        switch(netCode)
        {
        case NetworkValues::NOTIFY:
            notificationPacket(&packet);
            break;
        }
    }

    packet.clear();
    sf::IpAddress ip;
    unsigned short int remotePort(0);
    //status = gameServerUdpSocket.receive(packet, ip, remotePort);

    //if(status == sf::Socket::Status::Done)
    while(gameServerUdpSocket.receive(packet, ip, remotePort) == sf::Socket::Status::Done)
    {
        unsigned int netCode(0);
        packet >> netCode;

        switch(netCode)
        {
        case NetworkValues::UPDATE:
            unsigned long long number;
            packet >> number;

            if(number > udpPacketNumberReceive)
            {
                udpPacketNumberReceive = number;
                world.updateEntity(&packet);
            }
            break;
        }
    }
}

void Game::notificationPacket(sf::Packet* packet)
{
    unsigned int notifyType(0);
    *packet >> notifyType;

    switch(notifyType)
    {
        case NetworkValues::RECEIVE_CHAT_MESSAGE:
            {
                std::string message("");
                std::string username("");
                std::string text("");

                *packet >> username;
                *packet >> text;

                message  = "[" + username + "] " + text;
                chat.write(message);
            }
            break;
        case NetworkValues::PLAYER_CONNECTED :
            {
                std::string username("");
                std::string message("");

                *packet >> username;

                message = "[" + username + "] Viens de se connecter !";

                chat.write(message);
            }
            break;
        case NetworkValues::PLAYER_DISCONNECTED :
            {
                std::string username("");
                std::string message("");

                *packet >> username;

                message = "[" + username + "] Viens de se deconnecter !";

                chat.write(message);
            }
            break;
        case NetworkValues::ENTITY_REMOVED :
            {
                unsigned int entityId(0);
                *packet >> entityId;
                world.removeEntity(entityId);
            }
            break;
        default:
            break;
    }
}

void Game::sendInput()
{
    sf::Packet packet;
    packet << NetworkValues::INPUT << username << token << udpPacketNumber << playerInput.MoveUp << playerInput.MoveDown << playerInput.MoveLeft << playerInput.MoveRight;

    gameServerUdpSocket.send(packet, ip, 22623);
    udpPacketNumber++;
}

void Game::testInput()
{
    playerInput.MoveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    playerInput.MoveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    playerInput.MoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    playerInput.MoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Game::render(sf::RenderWindow* window)
{
    window->clear(sf::Color::White);

    window->draw(chat);
    window->draw(world);

    window->display();
}
