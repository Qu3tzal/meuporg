#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Entity.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include "Npc.hpp"
#include "../ResourceHolder.hpp"
#include "../SFMLPacketUtils.hpp"
#include "Map.hpp"
#include "Hud.hpp"
#include "DialogManager.hpp"
#include "Bullet.hpp"
#include "Tower.hpp"
#include "../NetworkValues.hpp"
#include "Chat.hpp"

class World : public sf::Drawable, public sf::Transformable
{
    public:
        World(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string* username, sf::RenderWindow* window, sf::TcpSocket* socket, Chat* chat);
        virtual ~World();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void removeEntity(unsigned int entityId);

        void updateEntity(sf::Packet* packet);

        void addEntity(unsigned int id, Entity::Type type, std::string name, sf::Vector2f position, sf::Vector2f velocity);

        Entity* getEntityById(unsigned int id);

        void loadMap(std::string path);

        void loadMap(int mapId);

        Player* getPlayer(std::string playerName);

        void changeWorld(int worldId, int mapId);

        void sendRespawnRequest(unsigned int spawnId);

        void entityKilled(unsigned int id);

        void setStaticView() const;

        void setGameView() const;

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

        DialogManager dialogs;

        unsigned int worldId;

        unsigned int mapId;

        sf::TcpSocket* socket;

        Chat* chat;

        sf::View staticView;

        sf::View playerCentredView;

        sf::RenderWindow* window;

    private:
};

#endif // WORLD_HPP
