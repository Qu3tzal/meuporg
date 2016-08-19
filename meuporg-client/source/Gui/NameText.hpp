#ifndef NAMETEXT_HPP
#define NAMETEXT_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include "../ResourceHolder.hpp"
#include "../Gui/GraphicsUtils.hpp"
#include "../ResourceId.hpp"
#include "sstream"

class NameText : public sf::Drawable, public sf::Transformable
{
    public:
        NameText(std::string text, kantan::FontHolder* fonts);
        virtual ~NameText();

        void setHealth(float health, float healthMax);

        int getheight();

    protected:

        // Draws the textInputs and button
        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        std::string name;

        sf::Text nameText;

        sf::RectangleShape nameBackground;

        sf::Text healthText;

        sf::RectangleShape healthBackground;

        kantan::FontHolder* fonts;

        bool ShowHealth;

    private:
};

#endif // NAMETEXT_HPP
