#ifndef NPC_HPP
#define NPC_HPP


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Entity.hpp"

class Npc : public Entity
{
    public:
        Npc(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string name, unsigned int id);
        virtual ~Npc();

        enum State {};

        virtual void init();

        virtual void update(sf::Time dt);

        void setState(State state);

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        State state;

    private:
};

#endif // NPC_HPP
