// Reading.
template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2<T>& vector)
{
    packet >> vector.x >> vector.y;

    return packet;
}

// Writing.
template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2<T>& vector)
{
	packet << vector.x << vector.y;

    return packet;
}
