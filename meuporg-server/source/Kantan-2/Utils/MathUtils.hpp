#ifndef KANTAN_MATHUTILS
#define KANTAN_MATHUTILS

#include <cmath>
#include <SFML/Graphics.hpp>

namespace kantan
{
	// Computes the euclidian distance between a and b.
	float euclidianDistance(const sf::Vector2f& a, const sf::Vector2f& b);
	float euclidianDistance(const sf::Vector3f& a, const sf::Vector3f& b);
	float euclidianDistance(const sf::FloatRect& a, const sf::FloatRect& b);

	// Computes the squared euclidian distance between a and b.
	float squaredEuclidianDistance(const sf::Vector2f& a, const sf::Vector2f& b);
	float squaredEuclidianDistance(const sf::Vector3f& a, const sf::Vector3f& b);
	float squaredEuclidianDistance(const sf::FloatRect& a, const sf::FloatRect& b);

	// Computes the manhattan distance between a and b.
	float manhattanDistance(const sf::Vector2f& a, const sf::Vector2f& b);

	// Computes the center of the given rectangle.
	sf::Vector2f centerRectangle(const sf::FloatRect& x);

	// Returns the length of the vector.
	float getLength(sf::Vector2f x);
	float getLength(sf::Vector3f x);

	// Returns the normalized vector.
	sf::Vector2f normalize(sf::Vector2f x);
	sf::Vector3f normalize(sf::Vector3f x);

	// Returns the dot product of two vectors.
	template <typename T>
    inline float dotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    // Returns the cross product of two vectors.
    template <typename T>
    inline sf::Vector3<T> crossProduct(const sf::Vector3<T>& a, const sf::Vector3<T>& b)
    {
        sf::Vector3<T> s;
        s.x = a.y * b.z - a.z * b.y;
        s.y = a.z * b.x - a.x * b.z;
        s.z = a.x * b.y - a.y * b.x;

        return s;
    }

    // Pi constants.
    #define M_PI    3.14159265358979323846
    #define M_PIl   3.141592653589793238462643383279502884L

} // namespace kantan.

#endif // KANTAN_MATHUTILS
