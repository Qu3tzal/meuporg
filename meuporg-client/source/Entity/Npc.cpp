#include "Npc.hpp"

Npc::Npc(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, sf::Uint64 id) : Entity(id, name, Entity::Type::NPC, textures, fonts)
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
