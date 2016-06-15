#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#include "Animation.hpp"
#include "Entity.hpp"
#include "NameText.hpp"


class Player : public Entity
{
    public:
        Player(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id);
        virtual ~Player();

        enum State {IDLE, WALKING};

        enum Direction{UP, DOWN, LEFT, RIGHT};

        virtual void init();

        virtual void update(sf::Time dt);

        void setState(State state);

        void setDirection();

        void calculatePrecision(sf::Vector2f vect);

        void setProperty(std::string name, float value);

        float getProperty(std::string name);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        State state;

        Animation a_MoveUp;
        Animation a_MoveDown;
        Animation a_MoveLeft;
        Animation a_MoveRight;

        Direction direction;

        sf::Sprite sprite;

        sf::Vector2f velocityNormalized;

        NameText nameText;

        std::map <std::string, float> m_properties;


    private:
};

#endif // PLAYER_HPP
