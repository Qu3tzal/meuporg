#include "Component.hpp"

namespace kantan
{
    /// Ctor.
    Component::Component(std::string name, std::size_t ownerId)
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
	std::size_t Component::getOwnerId() const
	{
        return m_ownerId;
	}
} // namespace kantan.
