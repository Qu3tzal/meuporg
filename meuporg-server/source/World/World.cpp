#include "World.hpp"

World::World()
{
}

World::~World()
{
    // Free the memory.
    for(kantan::Entity* e : m_entities)
        delete e;

    for(kantan::DeletionMarkerComponent* dmc : m_deletionMarkerComponents)
        delete dmc;

    for(kantan::PolygonHitboxComponent* phc : m_polygonHitboxComponents)
        delete phc;

    for(kantan::MovementComponent* mc : m_movementComponents)
        delete mc;

    for(kantan::RotationComponent* rc : m_rotationComponents)
        delete rc;
}

void World::init()
{

}

void World::update(sf::Time dt)
{
    // Rotations.
    m_rotationSystem.update(dt, m_polygonHitboxComponents, m_rotationComponents);

    // Collision.
    m_collisionSystem.update(dt, m_polygonHitboxComponents, m_movementComponents);

    // Clean the entities.
    cleanEntities();
}

void World::cleanEntities()
{
    for(std::size_t i(0) ; i < m_deletionMarkerComponents.size() ;)
    {
        kantan::DeletionMarkerComponent* dmc = m_deletionMarkerComponents[i];

        if(dmc->marked)
        {
            auto itr = std::find_if(m_entities.begin(), m_entities.end(), [dmc](kantan::Entity* e){
                            return dmc->getOwnerId() == e->getId();
                        });

            if(itr != m_entities.end())
            {
                kantan::Entity* entity = (*itr);
                std::unordered_map<std::string, kantan::Component*> components = entity->getAllComponents();

                for(std::pair<std::string, kantan::Component*> componentPair : components)
                {
                    kantan::Component* component = componentPair.second;

                    if(component->getName() == "DeletionMarker")
                        removeComponentFrom<kantan::DeletionMarkerComponent>(component, m_deletionMarkerComponents);
                    else if(component->getName() == "PolygonHitbox")
                        removeComponentFrom<kantan::PolygonHitboxComponent>(component, m_polygonHitboxComponents);
                    else if(component->getName() == "Movement")
                        removeComponentFrom<kantan::MovementComponent>(component, m_movementComponents);
                    else if(component->getName() == "Rotation")
                        removeComponentFrom<kantan::RotationComponent>(component, m_rotationComponents);
                }
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
}

kantan::Entity* World::createEntity(std::string name)
{
    kantan::Entity* e = new kantan::Entity(name);

    kantan::DeletionMarkerComponent* dmc = createDeletionMarkerComponent(e->getId());
    e->addComponent(dmc);

    m_entities.push_back(e);

    return e;
}

// createXXXComponent methods.
kantan::DeletionMarkerComponent* World::createDeletionMarkerComponent(std::size_t ownerId)
{
    kantan::DeletionMarkerComponent* dmc = new kantan::DeletionMarkerComponent(ownerId);
    m_deletionMarkerComponents.push_back(dmc);

    return dmc;
}

kantan::PolygonHitboxComponent* World::createPolygonHitboxComponent(std::size_t ownerId)
{
    kantan::PolygonHitboxComponent* phc = new kantan::PolygonHitboxComponent(ownerId);
    m_polygonHitboxComponents.push_back(phc);

    return phc;
}

kantan::MovementComponent* World::createMovementComponent(std::size_t ownerId)
{
    kantan::MovementComponent* mc = new kantan::MovementComponent(ownerId);
    m_movementComponents.push_back(mc);

    return mc;
}

kantan::RotationComponent* World::createRotationComponent(std::size_t ownerId)
{
    kantan::RotationComponent* rc = new kantan::RotationComponent(ownerId);
    m_rotationComponents.push_back(rc);

    return rc;
}

