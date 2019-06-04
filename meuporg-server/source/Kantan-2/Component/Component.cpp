#include "Component.hpp"

namespace kantan
{
    /// Ctor.
    Component::Component(std::string name, unsigned long long ownerId)
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
	unsigned long long Component::getOwnerId() const
	{
        return m_ownerId;
	}
} // namespace kantan.
