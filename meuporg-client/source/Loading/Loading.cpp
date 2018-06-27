#include "Loading.hpp"

Loading::Loading(sf::TcpSocket* informationSocket, sf::TcpSocket* serverSocket, sf::TcpSocket* gameServerSocket, sf::UdpSocket* gameServerUdpSocket, kantan::FontHolder* fonts, sf::RenderWindow* window, State* state, std::string* token, std::string* username) :
    buttons(window, fonts)
    , textInputs(window, fonts, 0)
    , showText(true)
    , Version(002)

{
    this->informationSocket = informationSocket;
    this->serverSocket = serverSocket;
    this->gameServerSocket = gameServerSocket;
    this->gameServerUdpSocket = gameServerUdpSocket;
    this->state = state;
    this->token = token;
    this->username = username;
    this->fonts = fonts;
}

Loading::~Loading()
{
    //dtor
}

void Loading::init()
{
    text.setFont(fonts->get(ResourceId::MONOF_56));
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Red);
    text.setPosition(575, 450);
    text.setString("");

    auto next = [this](){
    this->nextStep();};
    textInputs.addTextInput("name", sf::Vector2f(575, 200), sf::Vector2f(250, 50), "Rentrer votre pseudo", ResourceId::MONOF_56, 14, sf::Color(128, 128, 128, 128), sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(70, 70, 70, 128));
    textInputs.addTextInput("ip", sf::Vector2f(575, 325), sf::Vector2f(250, 50), "Rentrer l'ip", ResourceId::MONOF_56, 14, sf::Color(128, 128, 128, 128), sf::Color::White, sf::Color(128, 128, 128, 128), sf::Color(70, 70, 70, 128));
    buttons.addButton("valider", sf::Vector2f(600, 400), sf::Vector2f(100, 50), "Valider", ResourceId::MONOF_56, 14, sf::Color(128, 128, 128, 128), sf::Color(70, 70, 70, 128), next);
}

void Loading::nextStep()
{
    if(textInputs.getText("name") != "" && textInputs.getText("ip") != "")
    {
        ip = sf::IpAddress(textInputs.getText("ip"));
        *username = textInputs.getText("name");
        serverConnection();
    }
    else
    {
        text.setString("Veuillez remplir tout les champs");
    }
}

void Loading::update(sf::Time dt)
{
    buttons.update();
    textInputs.update();
}

void Loading::eventHandle(sf::Event e)
{
    buttons.handleEvent(e);
    textInputs.handleEvent(e);
}

void Loading::serverConnection()
{


    sf::Socket::Status status = informationSocket->connect(ip, 22626, sf::seconds(5.f));
    if (status != sf::Socket::Done)
    {
        text.setFillColor(sf::Color::Red);
        text.setString("Connection timed out");
        return;
    }

    sf::Packet packet;
    packet << NetworkValues::VERSION;
    informationSocket->send(packet);

    sf::Packet serverVersionPacket;
    informationSocket->receive(serverVersionPacket);

    packet.clear();

    packet << NetworkValues::NUMBER_OF_PLAYERS;
    informationSocket->send(packet);
    sf::Packet playerNumberPacket;
    informationSocket->receive(playerNumberPacket);

    unsigned int serverVersion;
    unsigned int playerNumber;
    unsigned int maximumPlayer;

    serverVersionPacket >> serverVersion;
    playerNumberPacket >> playerNumber >> maximumPlayer;

    //std::cout << "Server version : " <<  serverVersion << std::endl <<" Number of player : " << playerNumber << "/" <<  maximumPlayer << std::endl;

    connectToServer();
}

void Loading::connectToServer()
{
    sf::Packet packet;
    sf::TcpSocket::Status status = serverSocket->connect(ip, 22625, sf::seconds(5.f));

    if (status != sf::Socket::Done)
    {
        text.setFillColor(sf::Color::Red);
        text.setString("Connection timed out");
        return;
    }

    text.setFillColor(sf::Color::Black);
    text.setString("Connection en cours");

    packet << NetworkValues::CONNECT << *username << Version;
    serverSocket->send(packet);
    packet.clear();

    serverSocket->receive(packet);

    unsigned int answer;
    packet >> answer;
    switch(answer)
    {
        case NetworkValues::ACCOUNT_CREATED_RECONNECT :
            text.setFillColor(sf::Color::Black);
            text.setString("Création du compte");
            serverSocket->disconnect();

            // Reconnect to the server.
            connectToServer();
            break;
        case NetworkValues::CONNECTION_SUCCESS :
            {
                text.setFillColor(sf::Color::Black);
                text.setString("Connection reussi");

                packet >> *token;

                //std::cout << "[DEBUG] Token: " << *token << std::endl;
                connectToGameServer();
            }
            break;
        case NetworkValues::CONNECTION_FAIL_UNKNOWN_USER :
                text.setFillColor(sf::Color::Red);
                text.setString("Identifiant inconnu");
            break;
        case NetworkValues::CONNECTION_FAIL_VERSION_ERROR :
            text.setFillColor(sf::Color::Red);
            text.setString("Version invalide");
            break;
        case NetworkValues::CONNECTION_FAIL_SERVER_FULL :
            text.setFillColor(sf::Color::Red);
            text.setString("Le serveur est complet");
            break;
        case NetworkValues::CONNECTION_FAIL_UNKNOWN_ERROR :
            text.setFillColor(sf::Color::Red);
            text.setString("Erreur inconnu");
            break;
        case NetworkValues::CONNECTION_FAIL_ALREADY_CONNECTED :
            text.setFillColor(sf::Color::Red);
            text.setString("Vous êtes déjà connecté");
            break;
    }
}

void Loading::connectToGameServer()
{
    //std::cout << "---------- Attente de reponse du serveur ----------" << std::endl;
    sf::TcpSocket::Status status = gameServerSocket->connect(ip, 22624, sf::seconds(5.f));

    if (status != sf::Socket::Done)
    {
        text.setFillColor(sf::Color::Red);
        text.setString("Connection Timed Out");
        return;
    }
    //std::cout << "---------- Connexion en cours ----------" << std::endl;
    sf::Packet packet;
    packet << NetworkValues::CONNECT << *username << *token;

    gameServerSocket->send(packet);
    packet.clear();
    gameServerSocket->receive(packet);

    unsigned int answer;
    packet >> answer;

    if(answer == NetworkValues::OKAY)
    {
        packet.clear();
        packet << NetworkValues::CONNECT << *username << *token;

        gameServerSocket->setBlocking(false);
        gameServerUdpSocket->setBlocking(false);

        sf::Packet receivePacket;

        // While we didn't received anything, we keep sending on UDP.
        sf::Clock clock;
        while(gameServerSocket->receive(receivePacket) != sf::Socket::Done)
        {
            if(clock.getElapsedTime() >= sf::seconds(0.5f))
            {
                gameServerUdpSocket->send(packet, ip, 22623);
                clock.restart();
            }
        }

        gameServerSocket->setBlocking(true);

        receivePacket >> answer;

        if(answer == NetworkValues::OKAY)
        {
            //std::cout << "---------- Connexion reussi ----------" << std::endl;
            receivePacket.clear();
            gameServerSocket->receive(receivePacket);
            gameServerSocket->setBlocking(false);
            gameServerUdpSocket->setBlocking(false);
            int playerNumber = 0;
            receivePacket >> playerNumber;
            *state = State::JEU;

            //std::cout << "Liste des joueurs : " << std::endl;
            for(int i = 1 ; i <= playerNumber ; i++)
            {
               std::string playerName = "";
                receivePacket >> playerName;
                //std::cout << "\t" << "[" << i << "] " << playerName << std::endl;
            }
        }
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_WRONG_TOKEN)
    {
        text.setFillColor(sf::Color::Red);
        text.setString("Token invalide");
        //gameServerSocket->disconnect();
        //connectToGameServer();
    }
    else if(answer == NetworkValues::CONNECTION_FAIL_UNKNOWN_USER)
    {
        text.setFillColor(sf::Color::Red);
        text.setString("Nom inconnu");
        //gameServerSocket->disconnect();
        //connectToGameServer();
    }

}

sf::IpAddress Loading::getIp() const
{
    return ip;
}

void Loading::draw(sf::RenderTarget& window, sf::RenderStates states) const
{

    window.draw(textInputs);
    window.draw(buttons);
    window.draw(text);

}
