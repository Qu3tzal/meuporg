#ifndef GUITEXTINPUTPOOL_HPP
#define GUITEXTINPUTPOOL_HPP

#include <map>
#include <functional>

#include <SFML/Graphics.hpp>

#include "GraphicsUtils.hpp"

/**
    TextInput struct.
    Stores the data relative to a text input.
**/
struct TextInput
{
    sf::RectangleShape shape;
    sf::Text text;
    sf::Text placeholderText;
    sf::Color textColor;
    sf::Color borderLineColor;
    sf::Color focusedBorderLineColor;
    sf::Vector2f shapeMinSize;
};

/**
    GUITextInputPool class.
    Manages the texts and the events related to them.
**/
class GUITextInputPool : public sf::Drawable, public sf::Transformable
{
    public:
        // Ctor.
        GUITextInputPool();

        // Dtor.
        virtual ~GUITextInputPool();

        // Adds a text input with the given parameters.
        void addTextInput(std::string name, sf::Vector2f centerPosition, sf::Vector2f size, std::string placeholderTextString, unsigned int fontId, unsigned int charSize, sf::Color backgroundColor, sf::Color textColor, sf::Color borderLineColor, sf::Color focusedBorderLineColor);

		// Adds this text input.
		void addTextInput(std::string name, TextInput textInput);

        // Removes the text input.
        void removeTextInput(std::string name);

        // Updates.
        void update();

        // Handles events relative to the texts inputs.
        void handleEvent(sf::Event event);

        // Returns the text contained by the text input.
        sf::String getText(std::string name);

        // Sets the custom view to use.
        void setCustomView(const sf::View& v);

    protected:
        // Draws the text inputs.
        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    protected:

        // Stores the text inputs (name, shape).
        std::map<std::string, TextInput> m_texts;

        // Name of the focused text input.
        std::string m_focusedTextName;

        // Custom view.
        sf::View m_customView;

        // Custom view flag.
        bool m_useCustomView;
};
#endif // GUITEXTINPUTPOOL_HPP
