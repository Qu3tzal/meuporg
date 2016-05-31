#include "TextureLoader.hpp"

TextureLoader::TextureLoader()
{
    //ctor
    textures[TextureId::SAITAMA].loadFromFile("assets/saitama_spritesheet.png");
    textures[TextureId::SPARTIATE].loadFromFile("assets/spartan_spritesheet.png");
}

TextureLoader::~TextureLoader()
{
    //dtor
}

sf::Texture TextureLoader::get(TextureId id) const
{
    return textures.at(id);
}


