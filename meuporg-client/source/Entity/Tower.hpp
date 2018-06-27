#ifndef TOWER_HPP
#define TOWER_HPP

#include "EntityWithStats.hpp"

class Tower: public EntityWithStats
{
    public:
        Tower(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, sf::Uint64 id);
        virtual ~Tower();

        virtual void init();

        virtual void update(sf::Time dt);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;


    private:
};

#endif // TOWER_HPP
