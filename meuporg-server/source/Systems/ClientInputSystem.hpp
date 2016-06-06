#ifndef CLIENTINPUTSYSTEM_HPP_INCLUDED
#define CLIENTINPUTSYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/ClientLinkComponent.hpp"

/*
	ClientInputSystem class.
	System : client input system.
*/
class ClientInputSystem : public kantan::System
{
	public:
		// Ctor.
		ClientInputSystem();

		// Update.
		virtual void update(std::vector<ClientLinkComponent*>& clientLinkComponents, std::vector<kantan::Entity*>& entities);
};

#endif // CLIENTINPUTSYSTEM_HPP_INCLUDED
