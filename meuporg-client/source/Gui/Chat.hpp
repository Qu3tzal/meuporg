#ifndef CHAT_HPP
#define CHAT_HPP

#include <SFML/Network.hpp>

#include "GUIButtonPool.hpp"
#include "GUITextInputPool.hpp"
#include "../NetworkValues.hpp"

#include <string>
#include <functional>
#include <iostream>
#include "../ResourceId.hpp"

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

    protected:

    // Draws the textInputs and button
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    GUIButtonPool buttons;

    GUITextInputPool textInputs;

    sf::TcpSocket* socket;

    bool chatActiveFlag;

    private:
};

#endif // CHAT_HPP
