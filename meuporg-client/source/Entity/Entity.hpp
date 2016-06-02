#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>
#include "Animation.hpp"
#include "../ResourceHolder.hpp"

class Entity
{
    public:
        Entity(unsigned int id, std::string name, kantan::TextureHolder* textures);
        virtual ~Entity();

        // Initiate the entity
        void init();

        // Update the entity
        void update(sf::Time dt);


    protected:

         // enum of type
        enum Type {SAITAMA, SPARTIATE};

        // id
        unsigned int id;

        // Type
        Type type;

        std::string name;

        // Position
        sf::Vector2f position;

        // Velocity
        sf::Vector2f velocity;

        // ResouceHolder
        kantan::TextureHolder* textures;


    private:
};

#endif // ENTITY_HPP
