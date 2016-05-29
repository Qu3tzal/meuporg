#include "RandomNumberGenerator.hpp"

RandomNumberGenerator::RandomNumberGenerator()
    : m_rng(time(0))
{}

RandomNumberGenerator::~RandomNumberGenerator(){}

unsigned int RandomNumberGenerator::generate()
{
    return m_rng();
}
