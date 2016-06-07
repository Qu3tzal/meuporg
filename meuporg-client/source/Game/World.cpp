#include "World.hpp"

World::World(kantan::TextureHolder* textures, kantan::FontHolder* fonts)
{
    this->textures = textures;
    this->fonts = fonts;
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
        }
        *packet >> position
                >> velocity;
        entity->setPosition(position);
        entity->setVelocity(velocity);

        entity->init();
        entities.push_back(entity);


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

void World::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    for(auto it = entities.begin() ; it != entities.end() ; it++)
    {
        window.draw((**it));
    }
}
