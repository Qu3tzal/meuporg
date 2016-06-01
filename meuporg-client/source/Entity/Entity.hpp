#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>
#include "Animation.hpp"

class Entity
{
    public:
        Entity(unsigned int id, std::string name
               );
        virtual ~Entity();

        // Initiate the entity
        void Init();

        // Update the entity
        void update(sf::Time dt);


    protected:

         // enum of type
        enum Type {SAITAMA, SPARTIATE};

        // enum of state
        enum State {};

        // id
        unsigned int id;

        // Type
        Type type;

        std::string name;

        // Position
        sf::Vector2f position;

        // Velocity
        sf::Vector2f velocity;


    private:
};

#endif // ENTITY_HPP
