#ifndef MATHS_HPP_INCLUDED
#define MATHS_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

template<typename T>
inline sf::Vector2<T> getLeftTop(std::vector<sf::Vector2<T>> points)
{
    /// ! TODO: Check there is at least one point.
    sf::Vector2<T> leftTop(points[0].x, points[0].y);

    for(sf::Vector2<T> point : points)
    {
        if(point.x < leftTop.x)
            leftTop.x = point.x;

        if(point.y < leftTop.y)
            leftTop.y = point.y;
    }

    return leftTop;
}

#endif // MATHS_HPP_INCLUDED
