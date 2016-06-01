#include "Entity.hpp"

Entity::Entity(unsigned int id, std::string name)
{
    this->id = id;
    this->name = name;
    Init();
}

Entity::~Entity()
{
    //dtor
}

void Entity::Init()
{

}

void Entity::update(sf::Time dt)
{

}
