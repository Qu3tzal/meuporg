#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Game : public sf::Drawable
{
    public:
        Game();
        virtual ~Game();

        void init();

        void update(sf::Time dt);

    protected:
        void draw(sf::RenderTarget* target, sf::RenderStates* states) const;

    private:
};

#endif // GAME_HPP
