#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"


class Dialog : public sf::Drawable, public sf::Transformable
{
    public:
        Dialog(kantan::FontHolder* fonts);
        virtual ~Dialog();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void setText(std::vector<std::string> text);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    private:

        kantan::FontHolder* fonts;

        sf::RectangleShape background;

        sf::Text text;

        std::vector<std::string> texts;
};

#endif // DIALOG_HPP
