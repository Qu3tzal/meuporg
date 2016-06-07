#ifndef NAMETEXT_HPP
#define NAMETEXT_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "../ResourceHolder.hpp"
#include "../Gui/GraphicsUtils.hpp"

class NameText : public sf::Drawable, public sf::Transformable
{
    public:
        NameText(std::string text, kantan::FontHolder* fonts);
        virtual ~NameText();

    protected:

        // Draws the textInputs and button
        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        std::string nameText;

        sf::Text text;

        sf::RectangleShape shape;

        kantan::FontHolder* fonts;

    private:
};

#endif // NAMETEXT_HPP
