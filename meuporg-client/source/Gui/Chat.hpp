#ifndef CHAT_HPP
#define CHAT_HPP

#include <SFML/Network.hpp>

#include "GUIButtonPool.hpp"
#include "GUITextInputPool.hpp"
#include "../NetworkValues.hpp"

#include <string>
#include <functional>
#include <iostream>
#include <vector>

#include "../ResourceId.hpp"
#include "../ResourceHolder.hpp"

class Chat : public sf::Drawable, public sf::Transformable
{
    public:
        Chat(sf::RenderWindow* window, sf::TcpSocket* socket, kantan::FontHolder* fonts);
        virtual ~Chat();

        void init();

        void update();

        void write(std::string);

        void sendMessage();

        void handleEvent(sf::Event e);

        bool isActive();

        void initText(sf::Text* text);

        void up(float height);

    protected:

    // Draws the textInputs and button
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    GUIButtonPool buttons;

    GUITextInputPool textInputs;

    sf::TcpSocket* socket;

    bool chatActiveFlag;

    sf::RectangleShape background;

    std::vector<std::string> logChat;

    std::vector<sf::Text> logText;

    kantan::FontHolder* fonts;

    private:
};

#endif // CHAT_HPP
