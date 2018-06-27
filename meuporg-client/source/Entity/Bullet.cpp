#include "Bullet.hpp"

Bullet::Bullet(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, sf::Uint64 id, Entity::Type luncher)
    : Entity(id, name, Entity::Type::BULLET, textures, fonts)
{
    this->luncher = luncher;
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::init()
{
    sprite.setTexture(textures->get(ResourceId::BULLET));
    switch(luncher)
    {
    case Entity::Type::PLAYER:
        sprite.setTextureRect(sf::IntRect(0, 0, 6, 6));
        break;
    case Entity::Type::TOWER:
        sprite.setTextureRect(sf::IntRect(6, 0, 8, 8));
        break;
    default:
        sprite.setTextureRect(sf::IntRect(0, 0, 6, 6));
        break;
    }
}

void Bullet::update(sf::Time dt)
{

}

void Bullet::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}

