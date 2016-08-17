#ifndef MONSTERAISYSTEM_HPP_INCLUDED
#define MONSTERAISYSTEM_HPP_INCLUDED

#include "../Kantan-2/kantan.hpp"

#include "../Components/MonsterAIComponent.hpp"

#include <chrono>
#include <random>

/*
	MonsterAISystem class.
	System : simulates the monsters AI.
*/
class MonsterAISystem : public kantan::System
{
	public:
		// Ctor.
		MonsterAISystem();

		// Update.
		virtual void update(sf::Time dt, std::vector<kantan::Component*>& monsterAIComponents, std::vector<kantan::Component*>& movementComponents);

    protected:
        std::default_random_engine m_rng_generator;
        std::uniform_int_distribution<int> m_rng_distribution;
};

#endif // MONSTERAISYSTEM_HPP_INCLUDED
