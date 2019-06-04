template<typename T>
void centerOrigin(T& x)
{
	sf::FloatRect bounds = x.getLocalBounds();
	x.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}

template<typename T>
inline const sf::Vector2<T> getCenter(std::vector<sf::Vector2<T>> points)
{
    sf::Vector2<T> gravityCenter(0.f, 0.f);

    for(unsigned int i(0) ; i < points.size() ; i++)
        gravityCenter += points[i];

    gravityCenter /= (T)points.size();

    return gravityCenter;
}
