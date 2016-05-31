#ifndef FONTLOADER_HPP
#define FONTLOADER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class FontLoader
{
    public:
        FontLoader();
        virtual ~FontLoader();

        enum FontId{SECRET_CODE};

        // get the font with the fontId
        sf::Font get(FontId);

    protected:

    private:

        // Associate font id and font
        std::map<FontId, sf::Font> fonts;
};

#endif // FONTLOADER_HPP
