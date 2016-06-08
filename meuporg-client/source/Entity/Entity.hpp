#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/System.hpp>
#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"
//#include "../GraphicsUtils.inl"

class Entity : public sf::Drawable, public sf::Transformable
{
    public:

        // enum of type
        enum Type {PLAYER, NPC, BOX};

        Entity(unsigned int id, std::string name, Type type, kantan::TextureHolder* textures, kantan::FontHolder* fonts);

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

        void setType(Type type);

        sf::Vector2f getVelocity() const;

        void setVelocity(sf::Vector2f);

        sf::Vector2f normalize(sf::Vector2f vect);

        double distEucli(sf::Vector2f v1, sf::Vector2f v2);

        double getNorm(sf::Vector2f vect);

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

        kantan::FontHolder* fonts;


    private:
};

#endif // ENTITY_HPP
