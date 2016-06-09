#include "Chat.hpp"

Chat::Chat(sf::RenderWindow* window, sf::TcpSocket* socket, kantan::FontHolder* fonts) : buttons(window)
    , textInputs(window, fonts)
    , chatActiveFlag(false)
{
    this->socket = socket;
    this->fonts = fonts;
    //init();
}

Chat::~Chat()
{
    //dtor
}

void Chat::init()
{
    background.setSize(sf::Vector2f(150, 400));
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(128, 128, 128, 128));

    textInputs.addTextInput("Chat", sf::Vector2f(0, 400), sf::Vector2f(150, 50), "Ecrivez votre message", ResourceId::SECRET_CODE_FONT, 12, sf::Color(128, 128, 128, 128), sf::Color::Black, sf::Color(128, 128, 128, 128), sf::Color(50, 50, 50, 128));
}

void Chat::write(std::string message)
{
    logChat.push_back(message);

    sf::Text text;
    initText(&text);

    if(logText.size() > 0 )
    {
        text.setPosition(10, logText[logText.size()-1].getGlobalBounds().top + logText[logText.size()-1].getGlobalBounds().height + 5.f);
    }
    else
    {
        text.setPosition(10, 350);
    }

    std::string str = logChat[logChat.size()-1];

    unsigned int maxSize(50);

    if(str.length() >= maxSize)
    {
        for(unsigned int j = 1 ; j <= (unsigned int)(str.length()/maxSize); j++)
        {
            str.insert(j * maxSize , "\n");
        }
    }
    text.setString(str);
    logText.push_back(text);
    while(text.getGlobalBounds().top + text.getGlobalBounds().height > 800)
    {
        if(logText.size()> 0)
        {
            logText.erase(logText.begin());
            logChat.erase(logChat.begin());
        }
        if(logText.size()> 0)
            up(logText[0].getPosition().y - 100);
        else
            break;
    }

}

void Chat::up(float height)
{
    for(sf::Text text : logText)
    {
        text.setPosition(text.getPosition().x, text.getPosition().y - height);
    }
}

void Chat::initText(sf::Text* text)
{
    text->setColor(sf::Color::White);
    text->setCharacterSize(12);
    text->setFont(fonts->get(ResourceId::SECRET_CODE_FONT));
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
    if(textInputs.getFocusedName() == "Chat")
    {
        chatActiveFlag = true;
    }
    else
    {
        chatActiveFlag = false;
    }
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

bool Chat::isActive()
{
    return chatActiveFlag;
}

void Chat::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(buttons);
    window.draw(textInputs);
}
