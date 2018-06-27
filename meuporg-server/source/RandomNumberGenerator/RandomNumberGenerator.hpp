#ifndef RANDOMNUMBERGENERATOR_HPP_INCLUDED
#define RANDOMNUMBERGENERATOR_HPP_INCLUDED

#include <random>
#include <ctime>

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

        unsigned int generate();

    protected:
        // Generator.
        std::mt19937 m_rng;
};

#endif // RANDOMNUMBERGENERATOR_HPP_INCLUDED
