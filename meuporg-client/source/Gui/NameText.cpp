#include "NameText.hpp"

NameText::NameText(std::string name, kantan::FontHolder* fonts)
{
    this->nameText = name;
    this->fonts = fonts;

    text.setFont(fonts->get(ResourceId::SECRET_CODE_FONT));
    text.setCharacterSize(12);
    text.setColor(sf::Color::White);
    text.setString(this->nameText);

    shape.setSize(sf::Vector2f(text.getGlobalBounds().width + 20, text.getGlobalBounds().height + 20));
    shape.setFillColor(sf::Color(128, 128, 128, 128));

    text.setPosition(0, 0);

    centerOrigin(text);
    centerOrigin(shape);
}

NameText::~NameText()
{
    //dtor
}

void NameText::draw(sf::RenderTarget& window, sf::RenderStates states) const
{

    states.transform *= getTransform();
    window.draw(shape, states);
    window.draw(text, states);
}