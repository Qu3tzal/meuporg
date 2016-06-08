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

                sf::Vector2f inputVector(0.f, 0.f);

                if(clc->client->inputs.isMoveDownKeyPressed)
                {
                    inputVector.y += 1.f;
                }
                else if(clc->client->inputs.isMoveUpKeyPressed)
                {
                    inputVector.y -= 1.f;
                }

                if(clc->client->inputs.isMoveLeftKeyPressed)
                {
                    inputVector.x -= 1.f;
                }
                else if(clc->client->inputs.isMoveRightKeyPressed)
                {
                    inputVector.x += 1.f;
                }

                mc->velocity = sf::Vector2f(0.f, 0.f);
                mc->velocity = kantan::normalize(inputVector) * mc->maximumSpeed;
            }
        }
    }
}
