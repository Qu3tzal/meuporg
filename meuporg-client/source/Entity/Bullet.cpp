#include "Bullet.hpp"

Bullet::Bullet(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id): Entity(id, name, Entity::Type::BULLET, textures, fonts)
{
    //ctor
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::init()
{
    sprite.setTexture(textures->get(ResourceId::BULLET));
}

void Bullet::update(sf::Time dt)
{

}

void Bullet::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}

