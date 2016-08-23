#include "World.hpp"

World::World(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string* username, sf::RenderWindow* window, sf::TcpSocket* socket, Chat* chat) : m_map(textures)
    , player(nullptr)
    , hud(fonts, window)
    , dialogs(fonts)
{
    this->textures = textures;
    this->fonts = fonts;
    this->username = username;
    this->socket = socket;
    this->chat = chat;
    this->window = window;
    //loadMap("assets/level/level1.lvl");
}

World::~World()
{
    for(Entity* e : entities)
    {
        delete e;
    }
}

void World::init()
{
    staticView.setSize(window->getView().getSize());
    staticView.setCenter(window->getView().getCenter());

    playerCentredView = window->getView();

    hud.init();
    hud.setPosition(sf::Vector2f(410, 655));
    loadMap(0);
    //loadMap("assets/map/map1.txt");
    for(Entity* e : entities)
    {
        e->init();
    }
    dialogs.init();
    dialogs.setPosition(500, 500);

}

void World::update(sf::Time dt)
{
    for(Entity* e : entities)
    {
        e->update(dt);
    }
    hud.update(dt);
    dialogs.update(dt);
}

void World::removeEntity(unsigned int entityId)
{
    std::vector<Entity*>::iterator it;
    for(it = entities.begin() ; it != entities.end() ; )
    {
        if((*it)->getId() == entityId)
        {
            delete *it;
            entities.erase(it);

        }
        else
        {
            it++;
        }
    }

}

void World::updateEntity(sf::Packet* packet)
{
    unsigned int id(0);
    unsigned int type_ui;
    unsigned int state_ui;
    unsigned int worldId(0);

    // basic stats
    float hp;
    float maxHp;
    float strengh;
    float agility;
    float resistance;

    // level and xp
    float xp;
    float level;
    std::string name("");

    sf::Vector2f position;
    sf::Vector2f velocity;

    *packet >> worldId
            >> id
            >> type_ui
            >> name
            >> state_ui
            >> position
            >> velocity;

    if(this->worldId != worldId)
        return;

    Entity::Type type = static_cast<Entity::Type>(type_ui);
    Entity* e = getEntityById(id);

    if(e != nullptr)
    {
        switch(type)
        {
            case Entity::Type::PLAYER:
                {
                    Player* player = static_cast<Player*>(e);

                    Player::State state = static_cast<Player::State>(state_ui);
                    *packet >> hp
                    >> maxHp
                    >> strengh
                    >> agility
                    >> resistance
                    >> xp
                    >> level;
                   player->setState(state);
                   player->setProperty("Hp", hp);
                   player->setProperty("MaxHp", maxHp);
                   player->setProperty("Strengh", strengh);
                   player->setProperty("Agility", agility);
                   player->setProperty("Resist", resistance);
                   player->setProperty("Xp", xp);
                   player->setProperty("Level", level);
                }
                break;
            case Entity::Type::NPC:
                {
                    Npc* npc = static_cast<Npc*>(e);

                    Npc::State state = static_cast<Npc::State>(state_ui);

                    npc->setState(state);
                }
                break;
            case Entity::Type::MONSTER:
                {
                    Monster* monster = static_cast<Monster*>(e);

                    Monster::State state = static_cast<Monster::State>(state_ui);

                    monster->setState(state);
                }
                break;
            default:
                break;
        }
        e->setName(name);
        e->setPosition(position);
        e->setVelocity(velocity);
    }
    else
    {
        Entity* entity;
        switch(type)
        {
            case Entity::Type::PLAYER:
                {
                    entity = new Player(textures, fonts, name, id);
                    Player::State state = static_cast<Player::State>(state_ui);

                    Player* player = static_cast<Player*>(entity);

                    *packet >> hp
                    >> maxHp
                    >> strengh
                    >> agility
                    >> resistance
                    >> xp
                    >> level;

                    player->setState(state);
                    player->setProperty("Hp", hp, false);
                   player->setProperty("HpMax", maxHp, false);
                   player->setProperty("Strengh", strengh, false);
                   player->setProperty("Agility", agility, false);
                   player->setProperty("Resist", resistance, false);
                   player->setProperty("Xp", xp, false);
                   player->setProperty("Level", level, false);
                }
                break;
            case Entity::Type::NPC:
                {
                    entity = new Npc(textures, fonts, name, id);
                    Npc::State state = static_cast<Npc::State>(state_ui);

                    Npc* npc = static_cast<Npc*>(entity);

                    npc->setState(state);
                }
                break;
            case Entity::Type::MONSTER:
                {
                    entity = new Monster(textures, fonts, name, id);
                    Monster::State state = static_cast<Monster::State>(state_ui);

                    Monster* monster = static_cast<Monster*>(entity);

                    monster->setState(state);
                }
                break;
               case Entity::Type::BULLET:
                {
                    unsigned int luncherId(0);
                    *packet >> luncherId;
                    Entity* e = getEntityById(luncherId);
                    entity = new Bullet(textures, fonts, name, id, e->getType());
                }
                break;
               case Entity::Type::TOWER:
                {
                    entity = new Tower(textures, fonts, name, id);
                }
                break;
            default:
                return;
                break;
        }

        entity->setPosition(position);
        entity->setVelocity(velocity);

        entity->init();
        entities.push_back(entity);

        if(this->player == nullptr)
        {
            this->player = getPlayer(*username);
            hud.setPlayer(this->player);
        }


    }

}

void World::sendRespawnRequest(unsigned int spawnId)
{
    sf::Packet packet;
    packet << NetworkValues::RESPAWN << spawnId;

    socket->send(packet);
}

void World::entityKilled(unsigned int id)
{
    if(id == player->getId())
    {
        Dialog* dialog = dialogs.createDialog();
        DialogChoice* choice = dialog->addChoice();
        choice->title = "Point de réapation:";
        choice->possibilities["Spawn 1"] = 0;
        choice->callback = [this](int choice){this->sendRespawnRequest(choice);};
        dialog->next();
    }
}


void World::addEntity(unsigned int id, Entity::Type type, std::string name, sf::Vector2f position, sf::Vector2f velocity)
{

}

void World::changeWorld(int worldId, int mapId)
{
    this->worldId = worldId;
    this->mapId = mapId;

    for(Entity* e : entities)
    {
        delete e;
    }
    entities.clear();
    player = nullptr;
    hud.setPlayer(nullptr);

    loadMap(mapId);
}

Entity* World::getEntityById(unsigned int id)
{
    for(Entity* e : entities)
    {
        if(e->getId() == id)
        {
            return e;
        }
    }

    return nullptr;
}

Player* World::getPlayer(std::string playerName)
{
    for(Entity* e : entities)
    {
        if(e->getType() == Entity::Type::PLAYER)
        {
            Player* player = static_cast<Player*>(e);
            if(player->getName() == playerName)
            {
                return player;
            }
        }
    }

    return nullptr;
}

void World::handleEvent(sf::Event e)
{
    hud.handleEvent(e);
    dialogs.handleEvent(e);
}

void World::loadMap(std::string path)
{
    if(!m_map.loadLevelFromFile(path))
    {
        std::cout<<"marche pas";
    }
    else
    {
        std::cout<<"marche";
    }
}

void World::loadMap(int worldId)
{
    m_map.createMap(worldId);
}

void World::setStaticView() const
{
    // Set the static view.
    window->setView(staticView);
}

void World::setGameView() const
{
    sf::View view = window->getView();
    if(player != nullptr)
    {
        view.setCenter(player->getPosition().x, player->getPosition().y);
    }
    window->setView(view);
}

void World::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    setGameView();
    window.draw(m_map);

    for(auto it = entities.begin() ; it != entities.end() ; it++)
    {
        window.draw((**it));
    }
    // static view
    setStaticView();

    window.draw(*chat);
    window.draw(hud);
    window.draw(dialogs);

    // end of the static View
}
