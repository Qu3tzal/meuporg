#include "Hud.hpp"

Hud::Hud(kantan::FontHolder* fonts) : player(nullptr)
{
    this->fonts = fonts;
}

Hud::~Hud()
{
    //dtor
}

void Hud::init()
{
    healthBar.setPosition(sf::Vector2f(25, 15));
    healthBar.setFillColor(sf::Color(255, 0, 0, 128));

    healthText.setFont(fonts->get(ResourceId::MONOF_56));
    healthText.setCharacterSize(16);
    healthText.setPosition(135, 35 - healthText.getGlobalBounds().height/2);
    healthText.setColor(sf::Color::White);

    xpBar.setPosition(sf::Vector2f(25, 80));
    xpBar.setFillColor(sf::Color(0, 128, 255, 128));

    xpText.setFont(fonts->get(ResourceId::MONOF_56));
    xpText.setCharacterSize(16);
    xpText.setPosition(135, 105 - healthText.getGlobalBounds().height/2);
    xpText.setColor(sf::Color::White);

    background.setPosition(0, 0);
    background.setSize(sf::Vector2f(350, 145));
    background.setFillColor(sf::Color(128, 128, 128, 128));
}

void Hud::update(sf::Time dt)
{
    healthBar.setSize(sf::Vector2f(setRatioHp(), 50));
    xpBar.setSize(sf::Vector2f(setRatioXp(), 50));
}

unsigned int Hud::setRatioHp()
{
    if(player != nullptr)
    {
        std::stringstream ss;
        ss << player->getProperty("Hp") << " / " << player->getProperty("HpMax");
        healthText.setString(ss.str());
        float ratio = 300/player->getProperty("HpMax");
        return (player->getProperty("Hp") * ratio);
    }
    return 300;
}

unsigned int Hud::setRatioXp()
{
    if(player != nullptr)
    {
        std::stringstream ss;
        ss << player->getProperty("Xp") << " / " << player->getProperty("XpNeeded");
        xpText.setString(ss.str());
        float ratio = 300/player->getProperty("XpNeeded");
        return (player->getProperty("Xp") * ratio);
    }
    return 300;
}

void Hud::setPlayer(Player* p)
{
    this->player = p;
}

void Hud::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background, states);
    window.draw(healthBar, states);
    window.draw(xpBar, states);
    window.draw(healthText, states);
    window.draw(xpText, states);


}
