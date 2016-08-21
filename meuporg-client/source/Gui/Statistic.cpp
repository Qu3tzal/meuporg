#include "Statistic.hpp"

Statistic::Statistic(kantan::FontHolder* fonts)
{
    this->fonts = fonts;
}

Statistic::~Statistic()
{
    //dtor
}

void Statistic::init()
{
    background.setFillColor(sf::Color(200, 200, 200, 128));
    background.setSize(sf::Vector2f(300, 150));

    nameText.setPosition(sf::Vector2f(10, 10));
    nameText.setCharacterSize(24);
    nameText.setFont(fonts->get(ResourceId::KENPIXEL));
    nameText.setColor(sf::Color::White);

    statsText.setCharacterSize(16);
    statsText.setFont(fonts->get(ResourceId::KENPIXEL));
    statsText.setColor(sf::Color::White);
}

void Statistic::update(Player* p)
{
    std::stringstream ss;

    ss << "Name : " << p->getName() << "\nLevel : " << p->getProperty("Level");
    nameText.setString(ss.str());

    std::stringstream sst;

    sst << "Vie : " << p->getProperty("HpMax") << "\nForce : " << p->getProperty("Strengh") << "\n"
    << "Agilite : " << p->getProperty("Agility") << "\nArmure : " << p->getProperty("Resist");

    statsText.setString(sst.str());
    statsText.setPosition(sf::Vector2f(10, nameText.getGlobalBounds().top + nameText.getGlobalBounds().height + 10));

    sf::Vector2f b_size;
    if(nameText.getGlobalBounds().width > statsText.getGlobalBounds().width)
    {
        b_size.x = nameText.getGlobalBounds().width + 10;
    }
    else
    {
        b_size.x = statsText.getGlobalBounds().width + 10 ;
    }

    background.setSize(sf::Vector2f(b_size.x + 10 , statsText.getGlobalBounds().top + statsText.getGlobalBounds().height + 10));
}

void Statistic::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background, states);

    window.draw(nameText, states);
    window.draw(statsText, states);

}
