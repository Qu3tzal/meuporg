#include "World.hpp"

World::World(kantan::TextureHolder* textures, kantan::FontHolder* fonts, std::string* username, sf::RenderWindow* window) : m_map(textures)
    , player(nullptr)
    , hud(fonts, window)
    , dialog(fonts)
{
    this->textures = textures;
    this->fonts = fonts;
    this->username = username;
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
    hud.init();
    hud.setPosition(sf::Vector2f(410, 655));
    loadMap();
    for(Entity* e : entities)
    {
        e->init();
    }
    dialog.init();
    dialog.setText("Bonjours,................................., Salut,..........................................., Ca Marche ?..................");
    dialog.setPosition(500, 500);
}

void World::update(sf::Time dt)
{
    for(Entity* e : entities)
    {
        e->update(dt);
    }
    hud.update(dt);
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

    *packet >> id
            >> type_ui
            >> name
            >> state_ui
            >> position
            >> velocity
            >> hp
            >> maxHp
            >> strengh
            >> agility
            >> resistance
            >> xp
            >> level;

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
                    entity = new Npc(textures, fonts, name, id);
                    Npc::State state = static_cast<Npc::State>(state_ui);

                    Npc* npc = static_cast<Npc*>(entity);

                    npc->setState(state);
                }
                break;
            default:
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

void World::addEntity(unsigned int id, Entity::Type type, std::string name, sf::Vector2f position, sf::Vector2f velocity)
{

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
    dialog.handleEvent(e);
}

void World::loadMap(std::string path)
{
    if(!m_map.loadLevelFromFile(path))
    {
        loadMap();
    }
}

void World::loadMap()
{
    m_map.createMap();
}

void World::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(m_map);

    for(auto it = entities.begin() ; it != entities.end() ; it++)
    {
        window.draw((**it));
    }
    window.draw(dialog);

    window.draw(hud);

}
