#include "Tower.hpp"

Tower::Tower(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id):
     EntityWithStats(id, name, fonts, textures, Entity::Type::TOWER)
{
    setProperty("HpMax", 1, false);
    setProperty("Hp", 1, false);
    setProperty("Strengh", 0, false);
    setProperty("Agility", 0, false);
    setProperty("Resist", 0, false);
}

Tower::~Tower()
{
    //dtor
}

void Tower::init()
{
    sprite.setTexture(textures->get(ResourceId::TOWER));
}

void Tower::update(sf::Time dt)
{
    EntityWithStats::update(dt);
}

void Tower::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
    EntityWithStats::draw(window, states);
}
