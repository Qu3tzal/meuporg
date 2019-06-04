#include "Component.hpp"

namespace kantan
{
    /// Ctor.
    Component::Component(std::string name, unsigned int ownerId)
		: m_name(name)
		, m_ownerId(ownerId)
    {}

    /// Dtor.
    Component::~Component()
    {}

    /// Name.
	std::string Component::getName() const
	{
		return m_name;
	}

	/// Owner id.
	unsigned int Component::getOwnerId() const
	{
        return m_ownerId;
	}
} // namespace kantan.
