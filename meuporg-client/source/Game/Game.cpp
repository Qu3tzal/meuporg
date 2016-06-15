#include "Game.hpp"

Game::Game(sf::RenderWindow* window) : running(true)
    , token("")
    , udpPacketNumber(0)
    , udpPacketNumberReceive(0)
    , username("")
    , chat(window, &gameServerSocket, &fonts)
    , world(&textures, &fonts, &username)
    , loosedPacket(0)
    , timeOutTimer(sf::Time::Zero)
    , timeOut(sf::seconds(5.f))
    , state(State::CHARGEMENT)
    , loading(&informationSocket, &serverSocket, &gameServerSocket, &gameServerUdpSocket, &fonts, window, &state, &token, &username)
{
    //ctor
    fonts.load(ResourceId::SECRET_CODE_FONT, "assets/fonts/secrcode.ttf");
    fonts.load(ResourceId::MONOF_56, "assets/fonts/monof56.ttf");

    textures.load(ResourceId::SPARTIATE_TEXTURE, "assets/spartan_spritesheet.png");
    textures.load(ResourceId::ONE_PUNCH_MAN_TEXTURE, "assets/saitama_spritesheet.png");
    textures.load(ResourceId::TILESET, "assets/box.png");
}

Game::~Game()
{
    //dtor
    disconnectToGameServer();
}

void Game::init()
{
    loading.init();
    chat.setPosition(0, 400);
    chat.init();
    world.init();
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


void Game::receivePacket()
{
    timeOutTimer += sf::seconds(1/60.f);
    sf::Packet packet;
    //sf::Socket::Status status = gameServerSocket.receive(packet);

    //if(status == sf::Socket::Status::Done)
    while(gameServerSocket.receive(packet) == sf::Socket::Status::Done)
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
        timeOutTimer = sf::Time::Zero;
        unsigned int netCode(0);
        packet >> netCode;

        switch(netCode)
        {
        case NetworkValues::UPDATE:
            unsigned long long number;
            packet >> number;
            if(number - udpPacketNumberReceive > 1)
            {
                loosedPacket += (number - 1) - udpPacketNumberReceive;
                std::cout   << "[PACKET_LOSS] " << loosedPacket << " / " << udpPacketNumberReceive
                                            << " (" << (loosedPacket * 100.f) / (float)(udpPacketNumberReceive) << "%)" << std::endl;
            }
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

    gameServerUdpSocket.send(packet, loading.getIp(), 22623);
    udpPacketNumber++;
}

void Game::testInput()
{
    playerInput.MoveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    playerInput.MoveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    playerInput.MoveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    playerInput.MoveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Game::update(sf::Time dt)
{
    switch(state)
    {
        case State::MENU:

        break;
        case State::CHARGEMENT:
            loading.update(dt);
        break;
        case State::JEU :
            if(!chat.isActive())
            {
                testInput();
            }
            else
            {
                playerInput.MoveUp = playerInput.MoveDown = playerInput.MoveLeft = playerInput.MoveRight = false;
            }
            sendInput();
            receivePacket();
            world.update(dt);
            chat.update();
        break;
    }
    if(timeOutTimer >= timeOut)
    {
        std::cout << "Connection timed out" << std::endl;
        running = false;
    }
}

void Game::EventHandle(sf::Event event)
{
    switch(state)
    {
    case State::JEU :
        chat.handleEvent(event);
        break;
    case State::CHARGEMENT :
        loading.eventHandle(event);
        break;
    case State::MENU :
        break;
    }
}

void Game::render(sf::RenderWindow* window)
{
    window->clear(sf::Color::White);
    switch(state)
     {
         case State::MENU:
            break;
         case State::CHARGEMENT:
            window->draw(loading);
            break;
         case State::JEU:
            window->draw(world);
            window->draw(chat);
            break;
     }
    window->display();
}
