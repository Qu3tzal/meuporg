#ifndef KANTAN_GRAPH
#define KANTAN_GRAPH

#include <SFML/Graphics.hpp>

namespace kantan
{
	class GUIGraph : public sf::Transformable, public sf::Drawable
	{
		public:
			GUIGraph();
			virtual ~GUIGraph();

			void setSize(float x, float y);
			void setNumberOfPoints(unsigned int numberOfPoints);
			void addValue(float x, float y);
			void update(sf::Time dt);

		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		protected:
			std::vector<sf::Vector2f> m_values;

			unsigned int m_numberOfPoints;
			sf::Vector2f m_size;
			sf::VertexArray m_vertexArray;
	};
} // namespace kantan.

#endif // GRAPH_HPP
