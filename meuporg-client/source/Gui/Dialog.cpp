#include "Dialog.hpp"

Dialog::Dialog(kantan::FontHolder* fonts)
{
    this->fonts = fonts;
}

Dialog::~Dialog()
{
    //dtor
}

void Dialog::init()
{
    background.setFillColor(sf::Color(60, 60, 60, 60));

    text.setFont(fonts->get(ResourceId::MONOF_56));
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);
}

void Dialog::update(sf::Time dt)
{

}

void Dialog::handleEvent(sf::Event e)
{

}

void Dialog::setText(std::vector<std::string> texts)
{
    this->texts = texts;
}

void Dialog::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background);
    window.draw(text);
}
