#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>

class Entity
{
    public:
        Entity(unsigned int id, std::string name);
        virtual ~Entity();

    protected:

         // enum of type
        enum Type {};

        // enum of state
        enum State {};

        // id
        unsigned int id;

        // Type
        Type type;

        std::string name;

        // State
        State state;

        // Position
        sf::Vector2f position;

        // Velocity
        sf::Vector2f velocity;


    private:
};

#endif // ENTITY_HPP
