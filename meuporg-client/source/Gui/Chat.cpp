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
    buttons.addButton("Enter", sf::Vector2f(0.f, 0.f), sf::Vector2f(12, 24), "Entrer", FontLoader::FontId::SECRET_CODE, 12, sf::Color::White, sf::Color(10, 10, 10), sendMessageLambda);
    textInputs.addTextInput("Chat", sf::Vector2f(0.f, 0.f), sf::Vector2f(12, 48), "Ecrivez votre message", FontLoader::FontId::SECRET_CODE, 12, sf::Color::White, sf::Color::Black, sf::Color::Black, sf::Color::Black);
}

void Chat::write(std::string message)
{
    std::cout << message << std::endl;
}

void Chat::sendMessage()
{
    std::string message("");
    message = textInputs.getText("Chat");
    sf::Packet packet;

    packet << NetworkValues::SEND_CHAT_MESSAGE << message;

    socket->send(packet);
}

void Chat::update()
{
    buttons.update();
    textInputs.update();
}

void Chat::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(buttons);
    window.draw(textInputs);
}
