#ifndef SERVERCONFIGURATION_HPP_INCLUDED
#define SERVERCONFIGURATION_HPP_INCLUDED

#include <SFML/System.hpp>

namespace ServerConfiguration
{
    const unsigned int Version(002);
    const float TickPerSec(60.f);
    const sf::Time Ticktime = sf::seconds(1.f / TickPerSec);

    const sf::Time InformationServerTimeout = sf::seconds(5.f);
    const sf::Time LoginServerTimeout = sf::seconds(5.f);
    const sf::Time PendingSocketTimeout = sf::seconds(5.f);
    const sf::Time GameServerTimeout = sf::seconds(5.f);

    const unsigned int InformationPort(22626);
    const unsigned int LoginPort(22625);
    const unsigned int GameTCPPort(22624);
    const unsigned int GameUDPPort(22623);
} // namespace ServerConfiguration.

#endif // SERVERCONFIGURATION_HPP_INCLUDED
