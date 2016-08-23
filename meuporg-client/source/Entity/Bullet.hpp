#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"

class Bullet : public Entity
{
    public:
        Bullet(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id, Entity::Type luncher);
        virtual ~Bullet();

        virtual void init();

        virtual void update(sf::Time dt);


    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        sf::Sprite sprite;

        Entity::Type luncher;


    private:
};

#endif // BULLET_HPP
