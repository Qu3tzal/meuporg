#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../Entity/Entity.hpp"
#include "../Entity/Player.hpp"
#include "../Entity/Monster.hpp"
#include "../Entity/Npc.hpp"
#include "../ResourceHolder.hpp"
#include "../SFMLPacketUtils.hpp"
#include "Map.hpp"
#include "../Gui/Hud.hpp"
#include "../Gui/DialogManager.hpp"
#include "../Entity/Bullet.hpp"
#include "../Entity/Tower.hpp"
#include "../NetworkValues.hpp"
#include "../Gui/Chat.hpp"

class World : public sf::Drawable, public sf::Transformable
{
    public:
        World(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string* username, sf::RenderWindow* window, sf::TcpSocket* socket, Chat* chat, int * ping);
        virtual ~World();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void removeEntity(sf::Uint64 entityId);

        void updateEntity(sf::Packet* packet);

        void addEntity(sf::Uint64 id, Entity::Type type, std::string name, sf::Vector2f position, sf::Vector2f velocity);

        Entity* getEntityById(sf::Uint64 id);

        void loadMap(std::string path);

        void loadMap(int mapId);

        Player* getPlayer(std::string playerName);

        void changeWorld(int worldId, int mapId);

        void sendRespawnRequest(sf::Uint64 spawnId);

        void entityKilled(sf::Uint64 id);

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

        sf::Uint64 worldId;

        sf::Uint64 mapId;

        sf::TcpSocket* socket;

        Chat* chat;

        sf::View staticView;

        sf::View playerCentredView;

        sf::RenderWindow* window;

    private:
};

#endif // WORLD_HPP
