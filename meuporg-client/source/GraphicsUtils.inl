template<typename T>
void centerOrigin(T& x)
{
	sf::FloatRect bounds = x.getLocalBounds();
	x.setOrigin((int)(bounds.left + bounds.width / 2.f), (int)(bounds.top + bounds.height / 2.f));
}
