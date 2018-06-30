#include "SFMLPacketUtils.hpp"

// Reading.
sf::Packet& operator >>(sf::Packet& packet, sf::Time& time)
{
    sf::Int32 x;
    packet >> x;

    time = sf::milliseconds(x);

    return packet;
}

// Writing.
sf::Packet& operator <<(sf::Packet& packet, const sf::Time& time)
{
    return packet << time.asMilliseconds();
}
