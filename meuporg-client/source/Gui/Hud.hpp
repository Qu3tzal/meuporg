#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"
#include "Player.hpp"
#include "GUIButtonPool.hpp"
#include "Statistic.hpp"


class Hud : public sf::Drawable, public sf::Transformable
{
    public:
        Hud(kantan::FontHolder* fonts, sf::RenderWindow* window);
        virtual ~Hud();

        enum Tabs {NONE, STATS};

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        unsigned int setRatioHp();

        unsigned int setRatioXp();

        void setPlayer(Player* p);

        void tabIni(Tabs tab);

    protected:

         virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

         Player* player;

         sf::RectangleShape healthBar;
         sf::Text healthText;

         sf::RectangleShape xpBar;
         sf::Text xpText;

         sf::RectangleShape background;

         kantan::FontHolder* fonts;

         GUIButtonPool buttons;

         Tabs tab;

         Statistic stats;

    private:
};

#endif // HUD_HPP
