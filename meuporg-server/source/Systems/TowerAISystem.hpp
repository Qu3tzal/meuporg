#ifndef TOWERAISYSTEM_HPP_INCLUDED
#define TOWERAISYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/BasicStatsComponent.hpp"
#include "../Components/WeaponComponent.hpp"
#include "../Components/TowerAIComponent.hpp"

#include <chrono>
#include <random>

class World;

/*
	TowerAISystem class.
	System : simulates the towers AI.
*/
class TowerAISystem : public kantan::System
{
	public:
		// Ctor.
		TowerAISystem();

		// Update.
		virtual void update(World* world, sf::Time dt, kantan::PolygonCollisionSystem* collisionSystem, std::vector<kantan::Component*>& towerAIComponents, std::vector<kantan::Entity*>& entities);

    protected:
        std::default_random_engine m_rng_generator;
        std::uniform_int_distribution<int> m_rng_distribution;
};

#endif // TOWERAISYSTEM_HPP_INCLUDED
