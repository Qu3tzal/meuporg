#include "RandomNumberGenerator.hpp"

RandomNumberGenerator::RandomNumberGenerator()
    : m_rng(time(0))
{}

RandomNumberGenerator::~RandomNumberGenerator(){}

sf::Uint64 RandomNumberGenerator::generate()
{
    return m_rng();
}
