#ifndef SERVERCONFIGURATION_HPP_INCLUDED
#define SERVERCONFIGURATION_HPP_INCLUDED

#include <SFML/System.hpp>

namespace ServerConfiguration
{
    const sf::Uint64 Version(002);
    const float TickPerSec(60.f);
    const sf::Time Ticktime = sf::seconds(1.f / TickPerSec);
    const sf::Time LoginTicktime = 3.f * Ticktime;

    const sf::Time InformationServerTimeout = sf::seconds(5.f);
    const sf::Time LoginServerTimeout = sf::seconds(5.f);
    const sf::Time PendingSocketTimeout = sf::seconds(5.f);
    const sf::Time GameServerTimeout = sf::seconds(5.f);

    const sf::Uint64 InformationPort(22626);
    const sf::Uint64 LoginPort(22625);
    const sf::Uint64 GameTCPPort(22624);
    const sf::Uint64 GameUDPPort(22623);
} // namespace ServerConfiguration.

#endif // SERVERCONFIGURATION_HPP_INCLUDED
