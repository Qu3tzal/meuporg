#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entity.hpp"

class Tower: public Entity
{
    public:
        Tower(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id);
        virtual ~Tower();

        virtual void init();

        virtual void update(sf::Time dt);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        sf::Sprite sprite;

    private:
};

#endif // TOWER_HPP
