#include "ClientInputSystem.hpp"

// Ctor.
ClientInputSystem::ClientInputSystem(){}

// Update.
void ClientInputSystem::update(std::vector<ClientLinkComponent*>& clientLinkComponents, std::vector<kantan::Entity*>& entities)
{
    for(ClientLinkComponent* clc : clientLinkComponents)
    {
        // Prevent crashing.
        if(clc->client != nullptr)
        {
            kantan::Entity* entity = kantan::Entity::getEntityWithId(clc->getOwnerId(), entities);

            if(entity == nullptr)
                continue;

            // Check the entity has a movement component.
            if(entity->hasComponent("Movement"))
            {
                // Get the movement component.
                kantan::MovementComponent* mc = entity->getComponent<kantan::MovementComponent>("Movement");

                // Reset velocity.
                mc->velocity = sf::Vector2f(0.f, 0.f);

                if(clc->client->inputs.isMoveDownKeyPressed)
                {
                    mc->velocity.y += 100.f;
                }
                else if(clc->client->inputs.isMoveUpKeyPressed)
                {
                    mc->velocity.y -= 100.f;
                }

                if(clc->client->inputs.isMoveLeftKeyPressed)
                {
                    mc->velocity.x -= 100.f;
                }
                else if(clc->client->inputs.isMoveRightKeyPressed)
                {
                    mc->velocity.x += 100.f;
                }
            }
        }
    }
}
