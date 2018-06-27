#include "GUIGraph.hpp"

namespace kantan
{
	GUIGraph::GUIGraph()
		: m_numberOfPoints(0)
		, m_vertexArray(sf::LinesStrip)
	{
		//ctor
	}

	GUIGraph::~GUIGraph()
	{
		//dtor
	}

	void GUIGraph::setSize(float x, float y)
	{
		m_size = sf::Vector2f(x, y);
	}

	void GUIGraph::addValue(float x, float y)
	{
		m_values.push_back(sf::Vector2f(x, y));
	}

	void GUIGraph::update(sf::Time dt)
	{
		m_vertexArray.clear();
		float maxx(1);
		float maxy(1);

		sf::Uint64 start(0);
		sf::Uint64 end(std::min(m_numberOfPoints, m_values.size() - 1));

		if(m_numberOfPoints < m_values.size())
		{
			start = m_values.size() - m_numberOfPoints - 1;
			end = start + m_numberOfPoints;
		}

		for(sf::Uint64 i(start) ; i < end ; ++i)
		{
			if(m_values[i].x - m_values[start].x > maxx)
				maxx = m_values[i].x;

			if(m_values[i].y > maxy)
				maxy = m_values[i].y;
		}

		for(sf::Uint64 i(start) ; i < end ; ++i)
		{
			sf::Vertex point;
			point.color = sf::Color::Green;
			point.position = sf::Vector2f((m_values[i].x - m_values[start].x),
										  m_size.y - m_size.y * m_values[i].y / maxy);

			m_vertexArray.append(point);
		}
	}

	void GUIGraph::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_vertexArray);
	}

	void GUIGraph::setNumberOfPoints(std::size_t numberOfPoints)
	{
		m_numberOfPoints = numberOfPoints;
	}
} // namespace kantan.
