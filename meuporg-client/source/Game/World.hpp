#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Entity.hpp"
#include "Player.hpp"
#include "Npc.hpp"
#include "../ResourceHolder.hpp"
#include "../SFMLPacketUtils.hpp"
#include "Map.hpp"
#include "Hud.hpp"
#include "Dialog.hpp"

class World : public sf::Drawable, public sf::Transformable
{
    public:
        World(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string* username, sf::RenderWindow* window);
        virtual ~World();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void removeEntity(unsigned int entityId);

        void updateEntity(sf::Packet* packet);

        void addEntity(unsigned int id, Entity::Type type, std::string name, sf::Vector2f position, sf::Vector2f velocity);

        Entity* getEntityById(unsigned int id);

        void loadMap(std::string path);

        void loadMap();

        Player* getPlayer(std::string playerName);

    protected:

         void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    protected :

        std::vector<Entity*> entities;

        kantan::TextureHolder* textures;

        kantan::FontHolder* fonts;

        Map m_map;

        Player* player;

        std::string* username;

        Hud hud;

        Dialog dialog;

    private:
};

#endif // WORLD_HPP
