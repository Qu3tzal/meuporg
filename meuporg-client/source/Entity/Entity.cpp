#include "Entity.hpp"

Entity::Entity(unsigned int id, std::string name, kantan::TextureHolder* textures)
{
    this->id = id;
    this->name = name;
    this->textures = textures;
    init();
}

Entity::~Entity()
{
    //dtor
}

void Entity::init()
{

}

void Entity::update(sf::Time dt)
{

}
