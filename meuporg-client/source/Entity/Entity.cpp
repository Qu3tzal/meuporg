#include "Entity.hpp"

Entity::Entity(unsigned int id, std::string name)
{
    this->id = id;
    this->name = name;
}

Entity::~Entity()
{
    //dtor
}
