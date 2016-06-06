#include "Entity.hpp"

Entity::Entity(unsigned int id, std::string name, Entity::Type type, kantan::TextureHolder* textures)
{
    this->id = id;
    this->name = name;
    this->type = type;
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

void Entity::setType(Type type)
{
    this->type = type;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
