#include "NameText.hpp"

NameText::NameText(std::string name, kantan::FontHolder* fonts): ShowHealth(true)
{
    this->name = name;
    this->fonts = fonts;

    nameText.setFont(fonts->get(ResourceId::MONOF_56));
    nameText.setCharacterSize(12);
    nameText.setColor(sf::Color::White);
    nameText.setString(this->name);

    nameBackground.setSize(sf::Vector2f(nameText.getGlobalBounds().width + 20, nameText.getGlobalBounds().height + 20));
    nameBackground.setFillColor(sf::Color(128, 128, 128, 128));

    nameText.setPosition(0, 0);
    if(ShowHealth)
    {
        healthText.setFont(fonts->get(ResourceId::MONOF_56));
        healthText.setCharacterSize(12);
        healthText.setColor(sf::Color::Red);

        healthBackground.setSize(sf::Vector2f(healthText.getGlobalBounds().width + 20, healthText.getGlobalBounds().height + 20));
        healthBackground.setFillColor(sf::Color(128, 128, 128, 128));

        healthText.setPosition(0, nameBackground.getGlobalBounds().height);
        healthBackground.setPosition(sf::Vector2f(0, nameBackground.getGlobalBounds().height));

        centerOrigin(healthText);
        centerOrigin(healthBackground);
    }
    centerOrigin(nameText);
    centerOrigin(nameBackground);
}

NameText::~NameText()
{
    //dtor
}

void NameText::setHealth(float health, float healthMax)
{
    std::stringstream ss;
    ss << (int)health << "/" << (int)healthMax <<" PV";
    healthText.setString(ss.str());
    healthBackground.setSize(sf::Vector2f(healthText.getGlobalBounds().width + 20, healthText.getGlobalBounds().height + 20));

    centerOrigin(healthText);
    centerOrigin(healthBackground);
}

int NameText::getheight()
{
    return (nameBackground.getGlobalBounds().height + healthBackground.getGlobalBounds().height);
}

void NameText::draw(sf::RenderTarget& window, sf::RenderStates states) const
{

    states.transform *= getTransform();
    window.draw(nameBackground, states);
    if(ShowHealth)
        window.draw(healthBackground, states);
    window.draw(nameText, states);
    if(ShowHealth)
        window.draw(healthText, states);

}
