#include "FontLoader.hpp"

FontLoader::FontLoader()
{
    fonts[SECRET_CODE].loadFromFile("assets/fonts/secrcode.ttf");
}

FontLoader::~FontLoader()
{
    //dtor
}

sf::Font FontLoader::get(FontLoader::FontId id)
{
    return fonts[id];
}

