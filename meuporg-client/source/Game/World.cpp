#include "World.hpp"

World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}

void World::init()
{

}

void World::update(sf::Time dt)
{

}

void World::removeEntity(unsigned int entityId)
{
    std::vector<Entity>::iterator it;
    for(it = entities.begin() ; it != entities.end() ; )
    {
        if((*it).getId() == entityId)
        {
            entities.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void World::updateEntity(sf::Packet* packet)
{

}

void World::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    for(auto it = entities.begin() ; it != entities.end() ; it++)
    {
        window.draw((*it));
    }
}
