#include "PolygonHitboxComponent.hpp"

#include <string>

namespace kantan
{
    PolygonHitboxComponent::PolygonHitboxComponent(std::size_t ownerId, std::vector<sf::Vector2f> npoints)
                : kantan::Component(std::string("PolygonHitbox"), ownerId)
				, points(npoints)
                , isBlocking(true)
    {
		// Precompute the separation axes.
        computeAxes();
	}

    void PolygonHitboxComponent::computeAxes()
    {
        axes.clear();

        for(std::size_t i(0) ; i < points.size() ; i++)
		{
			sf::Vector2f a(0.f, 0.f), b(0.f, 0.f);

			if(i == points.size() - 1)
			{
				a = points[i];
				b = points[0];
			}
			else
			{
				a = points[i];
				b = points[i + 1];
			}

			sf::Vector2f c = b - a;
			float length = std::sqrt(std::pow(c.x, 2) + std::pow(c.y, 2));
			c /= length;

			sf::Vector2f axe(c);
			axe.x = -c.y;
			axe.y =  c.x;

			axes.push_back(axe);
		}
    }

    void PolygonHitboxComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Draw sides.
        sf::VertexArray va(sf::PrimitiveType::Lines);

        for(unsigned int i(1) ; i < points.size() ; i++)
        {
            sf::Vertex fst, snd;

            fst.position = points[i - 1];
            fst.color = sf::Color::Green;

            snd.position = points[i];
            snd.color = sf::Color::Green;

            va.append(fst);
            va.append(snd);
        }

        sf::Vertex fst, snd;

        fst.position = points[points.size() - 1];
        fst.color = sf::Color::Green;

        snd.position = points[0];
        snd.color = sf::Color::Green;

        va.append(fst);
        va.append(snd);

        target.draw(va, states);

        // Compute center.
        sf::Vector2f center(0.f, 0.f);
        for(sf::Vector2f point : points)
            center += point;
        center /= (float)points.size();

        //Draw axes.
        va.clear();

        for(sf::Vector2f axe : axes)
        {
            sf::Vertex fst, snd;

            fst.position = center;
            fst.color = sf::Color::Red;

            snd.position = center + axe * 10.f;
            snd.color = sf::Color::Red;

            va.append(fst);
            va.append(snd);
        }

        target.draw(va, states);
    }

} // namespace kantan.
