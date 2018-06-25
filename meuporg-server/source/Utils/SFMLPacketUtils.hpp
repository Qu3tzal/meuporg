#ifndef SFMLPACKETUTILS_HPP_INCLUDED
#define SFMLPACKETUTILS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

// Reading.
sf::Packet& operator >>(sf::Packet& packet, std::size_t& x);
sf::Packet& operator >>(sf::Packet& packet, sf::Time& time);
template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2<T>& vector);

// Writing.
sf::Packet& operator <<(sf::Packet& packet, std::size_t& x);
sf::Packet& operator <<(sf::Packet& packet, const sf::Time& time);
template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2<T>& vector);

#include "SFMLPacketUtils.inl"

#endif // SFMLPACKETUTILS_HPP_INCLUDED
