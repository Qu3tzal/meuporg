#ifndef NAMECOMPONENT_HPP_INCLUDED
#define NAMECOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

/*
	NameComponent class.
	Component : holds the xp and level.
*/
class NameComponent : public kantan::Component
{
	public:
		// Ctor.
		NameComponent(std::size_t ownerId);

		// Attribute.
		int id;
		std::string name;
};

#endif // NAMECOMPONENT_HPP_INCLUDED
