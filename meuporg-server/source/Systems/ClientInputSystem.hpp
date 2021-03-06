#ifndef CLIENTINPUTSYSTEM_HPP_INCLUDED
#define CLIENTINPUTSYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/ClientLinkComponent.hpp"

class World;

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
		virtual void update(std::vector<kantan::Component*>& clientLinkComponents, std::vector<kantan::Entity*>& entities, World* world);
};

#endif // CLIENTINPUTSYSTEM_HPP_INCLUDED
