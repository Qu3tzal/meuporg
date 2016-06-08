#include "Box.hpp"

Box::Box(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id) : Entity(id, name, Entity::Type::BOX ,textures, fonts)
{
    //ctor
}

Box::~Box()
{
    //dtor
}

void Box::init()
{
    sprite.setTexture(textures->get(ResourceId::BOX_TEXTURE));
}

void Box::update(sf::Time dt)
{

}

void Box::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();
    window.draw(sprite, states);
}
