#ifndef KANTAN_MATHUTILS
#define KANTAN_MATHUTILS

#include <cmath>
#include <SFML/Graphics.hpp>

namespace kantan
{
	// Computes the euclidian distance between a and b.
	float euclidianDistance(const sf::Vector2f& a, const sf::Vector2f& b);
	float euclidianDistance(const sf::FloatRect& a, const sf::FloatRect& b);

	// Computes the manhattan distance between a and b.
	float manhattanDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	// Computes the center of the given rectangle.
	sf::Vector2f centerRectangle(const sf::FloatRect& x);

	// Returns the length of the vector.
	float getLength(sf::Vector2f x);

	// Returns the normalized vector.
	sf::Vector2f normalize(sf::Vector2f x);

	// Returns the dot product of two vectors.
	template <typename T>
    inline float dotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
    {
        return a.x * b.x + a.y * b.y;
    }

} // namespace kantan.

#endif // KANTAN_MATHUTILS
