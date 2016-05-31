#ifndef CHAT_HPP
#define CHAT_HPP

#include <SFML/Network.hpp>

#include "GUIButtonPool.hpp"
#include "GUITextInputPool.hpp"
#include "../NetworkValues.hpp"

#include <string>
#include <functional>
#include <iostream>

class Chat : public sf::Drawable, public sf::Transformable
{
    public:
        Chat(sf::RenderWindow* window, sf::TcpSocket* socket);
        virtual ~Chat();

        void init();

        void update();

        void write(std::string);

        void sendMessage();

    protected:

    // Draws the textInputs and button
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    GUIButtonPool buttons;
    GUITextInputPool textInputs;

    sf::TcpSocket* socket;

    private:
};

#endif // CHAT_HPP