#include "World.hpp"

World::World(kantan::TextureHolder* textures, kantan::FontHolder* fonts) : m_map(textures)
    , player(nullptr)
{
    this->textures = textures;
    this->fonts = fonts;
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
    loadMap();
    for(Entity* e : entities)
    {
        e->init();
    }
}

void World::update(sf::Time dt)
{
    for(Entity* e : entities)
    {
        e->update(dt);
    }
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
    std::string name("");

    sf::Vector2f position;
    sf::Vector2f velocity;

    *packet >> id
            >> type_ui
            >> name;

    Entity::Type type = static_cast<Entity::Type>(type_ui);
    Entity* e = getEntityById(id);

    if(e != nullptr)
    {
        switch(type)
        {
            case Entity::Type::PLAYER:
                {
                   unsigned int state_ui;
                   Player* player = static_cast<Player*>(e);

                   *packet >> state_ui;

                   Player::State state = static_cast<Player::State>(state_ui);

                   player->setState(state);
                }
                break;
            case Entity::Type::NPC:
                {
                    unsigned int state_ui;
                    Npc* npc = static_cast<Npc*>(e);

                    *packet >> state_ui;

                    Npc::State state = static_cast<Npc::State>(state_ui);

                    npc->setState(state);
                }
                break;
            default:
                break;
        }
        *packet >> position
                >> velocity;
        e->setName(name);
        Player* player = static_cast<Player*>(e);
        player->calculatePrecision(position);
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
                    unsigned int state_ui;
                    *packet >> state_ui;


                    entity = new Player(textures, fonts, name, id);
                    Player::State state = static_cast<Player::State>(state_ui);

                    Player* player = static_cast<Player*>(entity);

                    player->setState(state);
                }
                break;
            case Entity::Type::NPC:
                {
                    unsigned int state_ui;
                    *packet >> state_ui;

                    entity = new Npc(textures, fonts, name, id);
                    Npc::State state = static_cast<Npc::State>(state_ui);

                    Npc* npc = static_cast<Npc*>(entity);

                    npc->setState(state);
                }
                break;
            default:
                break;
        }
        *packet >> position
                >> velocity;
        entity->setPosition(position);
        entity->setVelocity(velocity);

        entity->init();
        entities.push_back(entity);

        if(player == nullptr)
        {
            player = getPlayer(name);
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

}
