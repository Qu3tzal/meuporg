#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Entity.hpp"

class World : public sf::Drawable, public sf::Transformable
{
    public:
        World();
        virtual ~World();

        void init();

        void update(sf::Time dt);

        void removeEntity(unsigned int entityId);

        void updateEntity(sf::Packet* packet);
    protected:

         void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    protected :

        std::vector<Entity> entities;

    private:
};

#endif // WORLD_HPP
