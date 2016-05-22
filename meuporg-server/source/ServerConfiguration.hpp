#ifndef SERVERCONFIGURATION_HPP_INCLUDED
#define SERVERCONFIGURATION_HPP_INCLUDED

#include <SFML/System.hpp>

namespace ServerConfiguration
{
    const unsigned int Version(001);
    const float TickPerSec(60.f);
    const sf::Time Ticktime = sf::seconds(1.f / TickPerSec);
} // namespace ServerConfiguration.

#endif // SERVERCONFIGURATION_HPP_INCLUDED
