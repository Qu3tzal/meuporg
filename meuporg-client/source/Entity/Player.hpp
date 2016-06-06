#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

#include "Animation.hpp"
#include "Entity.hpp"


class Player : public Entity
{
    public:
        Player(kantan::TextureHolder* textures, std::string name, unsigned int id);
        virtual ~Player();

        enum STATE {IDLS, WALKING};

        virtual void init();

        virtual void update(sf::Time dt);

        void setState(STATE state);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        STATE state;

        Animation a_MoveUp;
        Animation a_MoveDown;
        Animation a_MoveLeft;
        Animation a_MoveRight;

        sf::Sprite sprite;
    private:
};

#endif // PLAYER_HPP
