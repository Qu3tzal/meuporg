#include "Entity.hpp"
#include "../Component/Component.hpp"

namespace kantan
{
    /// Static.
    unsigned int Entity::m_lastid = 0;

    Entity* Entity::getEntityWithId(unsigned int id, std::vector<Entity*>& entities)
    {
        auto itr = std::find_if(entities.begin(), entities.end(), [id](kantan::Entity* e){
                                    return e->getId() == id;
                    });

        if(itr == entities.end())
            return nullptr;

        return (*itr);
    }

	/// Ctor.
	Entity::Entity(std::string name)
		: m_id(m_lastid++)
		, m_name(name)
	{

	}

    /// Id.
	unsigned int Entity::getId() const
	{
		return m_id;
	}

	std::string Entity::getName() const
	{
		return m_name;
	}

	/// Components.
	void Entity::addComponent(Component* comp)
	{
		m_components[comp->getName()] = comp;
	}

	void Entity::removeComponent(std::string name)
	{
		auto it = m_components.find(name);

		if(it != m_components.end())
			m_components.erase(it);
	}

	bool Entity::hasComponent(std::string name)
	{
		return m_components.find(name) != m_components.end();
	}

	std::unordered_map<std::string, Component*> Entity::getAllComponents()
	{
        return m_components;
	}
} // namespace kantan.
