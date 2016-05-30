#ifndef KANTAN_GRAPHICSUTILS
#define KANTAN_GRAPHICSUTILS

#include <SFML/Graphics.hpp>

namespace kantan
{
	// Centers the origin of the given element.
	template<typename T>
	void centerOrigin(T& x);

    // Returns the center of the polygon.
    template<typename T>
    inline const sf::Vector2<T> getCenter(std::vector<sf::Vector2<T>> points);

	#include "GraphicsUtils.inl"
} // namespace kantan.

#endif // KANTAN_GRAPHICSUTILS
