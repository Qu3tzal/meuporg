#include "Npc.hpp"

Npc::Npc(kantan::TextureHolder* textures, std::string name, unsigned int id) : Entity(id, name, Entity::Type::NPC, textures)
{
    //ctor
}

Npc::~Npc()
{
    //dtor
}

void Npc::init()
{

}

void Npc::update(sf::Time dt)
{

}

void Npc::setState(Npc::State state)
{
    this->state = state;
}

void Npc::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}
