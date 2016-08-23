#include "MathUtils.hpp"

namespace kantan
{
	float euclidianDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	float euclidianDistance(const sf::Vector3f& a, const sf::Vector3f& b)
	{
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}

	float euclidianDistance(const sf::FloatRect& a, const sf::FloatRect& b)
	{
		return std::sqrt((a.left - b.left) * (a.left - b.left) + (a.top - b.top) * (a.top - b.top));
	}

	float squaredEuclidianDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

	float squaredEuclidianDistance(const sf::Vector3f& a, const sf::Vector3f& b)
	{
		return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
	}

	float squaredEuclidianDistance(const sf::FloatRect& a, const sf::FloatRect& b)
	{
		return ((a.left - b.left) * (a.left - b.left) + (a.top - b.top) * (a.top - b.top));
	}

	float manhattanDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return std::abs((float)(b.x - a.x)) / std::abs((float)(b.y - a.y));
	}

	sf::Vector2f centerRectangle(const sf::FloatRect& x)
	{
		return sf::Vector2f(x.left + x.width / 2, x.top + x.height / 2);
	}

	// Returns the length of the vector.
	float getLength(sf::Vector2f x)
	{
		return euclidianDistance(sf::Vector2f(0.f, 0.f), x);
	}

	float getLength(sf::Vector3f x)
	{
		return euclidianDistance(sf::Vector3f(0.f, 0.f, 0.f), x);
	}

	// Returns the normalized vector.
	sf::Vector2f normalize(sf::Vector2f x)
	{
	    float length = getLength(x);

        if(length == 0.f)
                return sf::Vector2f(0.f, 0.f);

		return x /= length;
	}

	sf::Vector3f normalize(sf::Vector3f x)
	{
		float length = getLength(x);

        if(length == 0.f)
                return sf::Vector3f(0.f, 0.f, 0.f);

		return x /= length;
	}
} // namespace kantan.
