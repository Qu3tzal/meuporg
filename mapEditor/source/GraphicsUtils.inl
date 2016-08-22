template<typename T>
void centerOrigin(T& x)
{
	sf::FloatRect bounds = x.getLocalBounds();
	x.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}
