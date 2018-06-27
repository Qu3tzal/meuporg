#ifndef RANDOMNUMBERGENERATOR_HPP_INCLUDED
#define RANDOMNUMBERGENERATOR_HPP_INCLUDED

#include <random>
#include <ctime>
#include <SFML/System.hpp>

/*
    RandomNumberGenerator class.
    Generates random numbers.
*/
class RandomNumberGenerator
{
    public:
        // Ctor.
        RandomNumberGenerator();

        // Dtor.
        virtual ~RandomNumberGenerator();

        sf::Uint64 generate();

    protected:
        // Generator.
        std::mt19937 m_rng;
};

#endif // RANDOMNUMBERGENERATOR_HPP_INCLUDED
