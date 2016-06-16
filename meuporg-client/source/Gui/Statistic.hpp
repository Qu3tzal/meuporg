#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <SFML/Graphics.hpp>

#include <sstream>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"
#include "Player.hpp"

class Statistic : public sf::Drawable, public sf::Transformable
{
    public:

        Statistic(kantan::FontHolder* fonts);
        virtual ~Statistic();

        void init();

        void update(Player* p);

    protected:

        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        kantan::FontHolder* fonts;

        sf::RectangleShape background;

        sf::Text nameText;

        sf::Text statsText;

    private:
};

#endif // STATISTIC_HPP
