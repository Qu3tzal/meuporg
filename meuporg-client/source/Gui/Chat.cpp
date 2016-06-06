#include "Chat.hpp"

Chat::Chat(sf::RenderWindow* window, sf::TcpSocket* socket, kantan::FontHolder* fonts) : buttons(window)
    , textInputs(window, fonts)
{
    this->socket = socket;
    //init();
}

Chat::~Chat()
{
    //dtor
}

void Chat::init()
{
    /*auto sendMessageLambda = [this](){
        this->sendMessage();};*/
    //buttons.addButton("Enter", sf::Vector2f(400.f, 50.f), sf::Vector2f(50, 50), "Entrer", FontLoader::FontId::SECRET_CODE, 12, sf::Color(128, 128, 128, 128), sf::Color(60, 60, 60, 128), sendMessageLambda);
    textInputs.addTextInput("Chat", sf::Vector2f(200.f, 50.f), sf::Vector2f(150, 50), "Ecrivez votre message", 1, 12, sf::Color(128, 128, 128, 128), sf::Color::Black, sf::Color(128, 128, 128, 128), sf::Color::Red);
}

void Chat::write(std::string message)
{
    std::cout << message << std::endl;
}

void Chat::sendMessage()
{
    std::string message("");
    message = textInputs.getText("Chat");
    textInputs.clear("Chat");
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
    if(textInputs.getFocusedName() == "Chat")
    {
        if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return && textInputs.getText("Chat") != "")
        {
            sendMessage();
        }
    }
}

void Chat::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(buttons);
    window.draw(textInputs);
}
