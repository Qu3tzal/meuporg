#include "Chat.hpp"

Chat::Chat(sf::RenderWindow* window, sf::TcpSocket* socket) : buttons(window)
    , textInputs(window)
{
    this->socket = socket;
    init();
}

Chat::~Chat()
{
    //dtor
}

void Chat::init()
{
    auto sendMessageLambda = [this](){
        this->sendMessage();};
    buttons.addButton("Enter", sf::Vector2f(400.f, 50.f), sf::Vector2f(50, 50), "Entrer", FontLoader::FontId::SECRET_CODE, 12, sf::Color(128, 128, 128, 128), sf::Color(60, 60, 60, 128), sendMessageLambda);
    textInputs.addTextInput("Chat", sf::Vector2f(200.f, 50.f), sf::Vector2f(150, 50), "Ecrivez votre message", FontLoader::FontId::SECRET_CODE, 12, sf::Color(128, 128, 128, 128), sf::Color::Black, sf::Color(128, 128, 128, 128), sf::Color::Red);
}

void Chat::write(std::string message)
{
    std::cout << message << std::endl;
}

void Chat::sendMessage()
{
    std::cout << "Send" << std::endl;
    std::string message("");
    message = textInputs.getText("Chat");
    textInputs.getText("Chat") = "";
    sf::Packet packet;

    packet << NetworkValues::SEND_CHAT_MESSAGE << message;

    socket->send(packet);
}

void Chat::update()
{
    buttons.update();
    textInputs.update();
}

void Chat::handleEvent(sf::Event e)
{
    buttons.handleEvent(e);
    textInputs.handleEvent(e);
}

void Chat::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(buttons);
    window.draw(textInputs);
}
