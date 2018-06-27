#ifndef KANTAN_GUIBUTTONPOOL
#define KANTAN_GUIBUTTONPOOL

#include <map>
#include <functional>

#include <SFML/Graphics.hpp>

#include "../ResourceHolder/ResourceHolder.hpp"
#include "../Utils/GraphicsUtils.hpp"

namespace kantan
{
	/**
		Button struct.
		Stores the data relative to a button.
	**/
	struct Button
	{
		sf::RectangleShape shape;
		sf::Text text;
		sf::Color color;
		sf::Color hoverColor;
		std::function<void()> fn;
	};

	/**
		GUIButtonPool class.
		Manages the buttons and the events related to them.
	**/
	class GUIButtonPool : public sf::Drawable, public sf::Transformable
	{
		public:
			// Ctor.
			GUIButtonPool(sf::RenderWindow* window, FontHolder* fonts);

			// Dtor.
			virtual ~GUIButtonPool();

			// Adds a button with the given parameters.
			void addButton(std::string name, sf::Vector2f centerPosition, sf::Vector2f size, std::string textString, sf::Uint64 fontId, sf::Uint64 charSize, sf::Color backgroundColor, sf::Color hoverBackgroundColor, std::function<void()> fn);

			// Adds this button.
			void addButton(std::string name, Button button);

			// Removes the button.
			void removeButton(std::string name);

			// Updates.
			void update();

			// Handles events relative to the buttons.
			void handleEvent(sf::Event event);

			// Sets the custom view to use.
			void setCustomView(const sf::View& v);

		protected:
			void draw(sf::RenderTarget& window, sf::RenderStates states) const;

		protected:
			// Window ptr.
			sf::RenderWindow* m_window;

			// Fonts holder.
			FontHolder* m_fonts;

			// Stores the buttons (name, shape).
			std::map<std::string, Button> m_buttons;

			// Custom view.
			sf::View m_customView;

			// Custom view flag.
			bool m_useCustomView;
	};
} // namespace kantan.

#endif // KANTAN_GUIBUTTONPOOL
