#include "Entity.hpp"

Entity::Entity(unsigned int id, std::string name, kantan::TextureHolder* textures)
{
    this->id = id;
    this->name = name;
    this->textures = textures;
}

Entity::~Entity()
{
    //dtor
}

unsigned int Entity::getId() const
{
    return id;
}

void Entity::setId(unsigned int id)
{
    this->id = id;
}

std::string Entity::getName() const
{
    return name;
}

void Entity::setName(std::string name)
{
    this->name = name;
}

Entity::Type Entity::getType() const
{
    return type;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
