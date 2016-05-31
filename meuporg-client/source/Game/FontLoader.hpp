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

        enum FontId{};

        sf::Font get(FontId);

        sf::Font load(std::string path);

    protected:

    private:

         std::map <FontId, sf::Font> fonts;
};

#endif // FONTLOADER_HPP
