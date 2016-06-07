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

void Entity::update(sf::Time dt)
{
    // Position prediction based on the movement.
    if(velocity != sf::Vector2f(0.f, 0.f))
    {
        setPosition(getPosition() + velocity * dt.asSeconds());
    }
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

sf::Vector2f Entity::normalize(sf::Vector2f vect)
{
    float norm = std::sqrt(std::pow(vect.x, 2) + std::pow(vect.y, 2));
    return sf::Vector2f(vect.x / norm, vect.y / norm);
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    this->velocity = velocity;
}
