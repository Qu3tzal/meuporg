#ifndef STATICMARKERCOMPONENT_HPP_INCLUDED
#define STATICMARKERCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"
#include "../Accounts.hpp"

/*
	StaticMarkerComponent class.
	Component : mark an entity as static (constant).
*/
class StaticMarkerComponent : public kantan::Component
{
	public:
		// Ctor.
		StaticMarkerComponent(unsigned int ownerId);

		// Attribute.
		bool isStatic;
};

#endif // STATICMARKERCOMPONENT_HPP_INCLUDED
