#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include<../ResourceHolder.hpp>
#include <../ResourceId.hpp>
#include <Player.hpp>
#include <sstream>

class Hud : public sf::Drawable, public sf::Transformable
{
    public:
        Hud(kantan::FontHolder* fonts);
        virtual ~Hud();

        void init();

        void update(sf::Time dt);

        unsigned int setRatioHp();

        unsigned int setRatioXp();

        void setPlayer(Player* p);

    protected:

         virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

         Player* player;

         sf::RectangleShape healthBar;
         sf::Text healthText;

         sf::RectangleShape xpBar;
         sf::Text xpText;

         sf::RectangleShape background;

         kantan::FontHolder* fonts;

    private:
};

#endif // HUD_HPP
