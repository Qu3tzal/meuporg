#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>
#include "../ResourceHolder.hpp"

class Entity : public sf::Drawable, public sf::Transformable
{
    public:
        Entity(unsigned int id, std::string name, kantan::TextureHolder* textures);

        // enum of type
        enum Type {SAITAMA, SPARTIATE};

        virtual ~Entity();

        // Initiate the entity
        virtual void init() = 0;

        // Update the entity
        virtual void update(sf::Time dt) = 0;

        unsigned int getId() const;

        void setId(unsigned int id);

        std::string getName() const;

        void setName(std::string);

        Type getType() const;

        sf::Vector2f getVelocity() const;

        void setVelocity(sf::Vector2f);

    protected:

         virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

    protected:
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
