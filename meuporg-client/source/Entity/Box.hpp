#ifndef BOX_HPP
#define BOX_HPP

#include "Entity.hpp"

class Box : public Entity
{
    public:
         Box(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id);
        virtual ~Box();

        virtual void init();

        virtual void update(sf::Time dt);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        sf::Sprite sprite;

    private:
};

#endif // BOX_HPP
