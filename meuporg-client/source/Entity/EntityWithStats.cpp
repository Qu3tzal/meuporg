#include "EntityWithStats.hpp"

EntityWithStats::EntityWithStats(unsigned int id, std::string name, kantan::FontHolder* fonts, kantan::TextureHolder* textures, Entity::Type type)
    : Entity(id, name, type, textures, fonts)
    , nameText(name, fonts)
{
    //ctor
}

EntityWithStats::~EntityWithStats()
{
    //dtor
}

void EntityWithStats::init()
{

}

void EntityWithStats::update(sf::Time dt)
{
        // Left hitMarker
    for(auto i = leftDamagesText.begin() ; i != leftDamagesText.end();)
    {
        if(i->getFillColor().a > 1)
        {
            i->setFillColor(sf::Color(i->getFillColor().r, i->getFillColor().g, i->getFillColor().b, i->getFillColor().a - 2));
            i->setPosition(i->getPosition().x, i->getPosition().y - 1);
            i++;
        }
        else
        {
            leftDamagesText.erase(i);
        }
    }
    // Right hitMarker
    for(auto i = rightDamagesText.begin() ; i != rightDamagesText.end();)
    {
        if(i->getFillColor().a > 1)
        {
            i->setFillColor(sf::Color(i->getFillColor().r, i->getFillColor().g, i->getFillColor().b, i->getFillColor().a - 2));
            i->setPosition(i->getPosition().x, i->getPosition().y - 1);
            i++;
        }
        else
        {
            rightDamagesText.erase(i);
        }
    }
    // Top hitMarker
    for(auto i = topDamagesText.begin() ; i != topDamagesText.end();)
    {
        if(i->getFillColor().a > 1)
        {
            i->setFillColor(sf::Color(i->getFillColor().r, i->getFillColor().g, i->getFillColor().b, i->getFillColor().a - 2));
            i->setPosition(i->getPosition().x, i->getPosition().y - 1);
            i++;
        }
        else
        {
            topDamagesText.erase(i);
        }
    }

    // centerOrigin(nametext);
    nameText.setPosition((int)(sprite.getGlobalBounds().width / 2 - sprite.getOrigin().x), (int)(- (nameText.getheight()) - sprite.getOrigin().y));
    nameText.setHealth(getProperty("Hp"),getProperty("HpMax"));
}

void EntityWithStats::setProperty(std::string name, float value, bool show)
{
    if(show)
     {
         if(name == "Hp")
         {
             float health = m_properties[name];
             if(health != value)
             {

                 sf::Text text;
                 text.setFont(fonts->get(ResourceId::KENPIXEL));
                 text.setCharacterSize(12);


                if(value > health)
                {
                    text.setFillColor(sf::Color(0, 255, 0, 255));
                    std::stringstream ss;
                    float nb = value - health;
                    ss << "+ " << nb;
                    text.setString(ss.str());
                }
                else
                {
                    text.setFillColor(sf::Color(255, 0, 0, 255));
                    std::stringstream ss;
                    float nb = health - value;
                    ss << "- " << nb;
                    text.setString(ss.str());
                }
                text.setPosition((int)(- (text.getGlobalBounds().width + 5 )), (int)(sprite.getGlobalBounds().height / 2));
                leftDamagesText.push_back(text);

             }
         }
         else if(name == "Xp")
         {
             float xp = m_properties[name];
             if(xp != value)
             {
                if(value > xp)
                {
                    sf::Text text;
                    text.setFont(fonts->get(ResourceId::KENPIXEL));
                    text.setCharacterSize(15);

                    text.setFillColor(sf::Color(0, 0, 255, 255));
                    std::stringstream ss;
                    float nb = value - xp;
                    ss << "+ " << nb << " XP";
                    text.setString(ss.str());

                    text.setPosition((int)(sprite.getGlobalBounds().width + 5 ),(int)( sprite.getGlobalBounds().height / 2));
                    rightDamagesText.push_back(text);
                }
             }
         }
         else if(name == "Level")
         {
             float level = m_properties[name];

             if(level != value)
             {
                sf::Text text;
                text.setFont(fonts->get(ResourceId::KENPIXEL));
                text.setCharacterSize(20);

                text.setFillColor(sf::Color(255, 215, 0, 255));
                std::stringstream ss;
                ss << "LEVEL UP!";
                text.setString(ss.str());

                centerOrigin(text);
                text.setPosition((int)(sprite.getGlobalBounds().width / 2), (int)( - (text.getGlobalBounds().height + 5)));
                topDamagesText.push_back(text);
             }
         }
    }
    m_properties[name] = value;
}

void EntityWithStats::setProperty(std::string name, float value)
{
    setProperty(name, value, true);
}

float EntityWithStats::getProperty(std::string name)
{
    return m_properties[name];
}

void EntityWithStats::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    //states.transform *= getTransform();
    window.draw(nameText, states);
    for(sf::Text text : leftDamagesText)
        window.draw(text, states);
    for(sf::Text text : rightDamagesText)
        window.draw(text, states);
    for(sf::Text text : topDamagesText)
        window.draw(text, states);
}
