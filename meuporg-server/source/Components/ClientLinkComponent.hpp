#ifndef CLIENTLINKCOMPONENT_HPP_INCLUDED
#define CLIENTLINKCOMPONENT_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"
#include "../Accounts.hpp"

/*
	ClientLinkComponent class.
	Component : link between an entity and a (network) client.
*/
class ClientLinkComponent : public kantan::Component
{
	public:
		// Ctor.
		ClientLinkComponent(unsigned int ownerId);

		// Attribute.
		Client* client;
		int dbid;
};

#endif // CLIENTLINKCOMPONENT_HPP_INCLUDED
