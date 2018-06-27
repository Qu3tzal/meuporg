#ifndef ENTITYWITHSTATS_HPP
#define ENTITYWITHSTATS_HPP

#include "Entity.hpp"
#include "../Gui/NameText.hpp"

class EntityWithStats : public Entity
{
    public:
        EntityWithStats(unsigned int id, std::string name, kantan::FontHolder* fonts, kantan::TextureHolder* textures, Entity::Type type);
        virtual ~EntityWithStats();

        void setProperty(std::string name, float value, bool show);

        void setProperty(std::string name, float value);

        float getProperty(std::string name);

        virtual void init();

        virtual void update(sf::Time dt);


    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        NameText nameText;

        std::map <std::string, float> m_properties;

        std::vector<sf::Text> leftDamagesText;
        std::vector<sf::Text> rightDamagesText;
        std::vector<sf::Text> topDamagesText;

    private:
};

#endif // ENTITYWITHSTATS_HPP
