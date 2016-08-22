#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Game : public sf::Drawable
{
    public:
        Game(sf::RenderWindow* window);
        virtual ~Game();

        void init();

        void update(sf::Time dt);

        void EventHandle(sf::Event e);

        bool isRunning();

    protected:
        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        bool run;

    private:
};

#endif // GAME_HPP
