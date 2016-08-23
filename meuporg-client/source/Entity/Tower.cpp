#include "Tower.hpp"

Tower::Tower(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id)
    :Entity(id, name, Entity::Type::BULLET, textures, fonts)
{
    //ctor
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

}

void Tower::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}
