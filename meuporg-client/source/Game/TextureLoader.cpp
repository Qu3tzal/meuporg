#include "TextureLoader.hpp"

TextureLoader::TextureLoader()
{
    //ctor
    textures[TextureId::SAITAMA] = load("../assets/saitama_spritesheet.png");
    textures[TextureId::SPARTIATE] = load("../assets/spartan_spritesheet.png");
}

TextureLoader::~TextureLoader()
{
    //dtor
}

sf::Texture TextureLoader::getTexture(TextureId id) const
{
    return textures.at(id);
}

sf::Texture TextureLoader::load(std::string path)
{
    sf::Texture texture;
    return texture;
}
