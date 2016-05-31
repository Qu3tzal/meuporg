#include "GUITextInputPool.hpp"

GUITextInputPool::GUITextInputPool(sf::RenderWindow* window) :
    m_focusedTextName("")
    , m_useCustomView(false)
{
    this->window = window;
    font.loadFromFile("assets/fonts/secrcode.ttf");
}

GUITextInputPool::~GUITextInputPool()
{
}

void GUITextInputPool::addTextInput(std::string name, sf::Vector2f centerPosition, sf::Vector2f size, std::string placeholderTextString, FontLoader::FontId fontId, unsigned int charSize, sf::Color backgroundColor, sf::Color textColor, sf::Color borderLineColor, sf::Color focusedBorderLineColor)
{
    sf::Text text, placeholderText;
    //text.setFont(fonts.get(fontId));
    text.setFont(font);
    //placeholderText.setFont(fonts.get(fontId));
    placeholderText.setFont(font);

    text.setCharacterSize(charSize);
    placeholderText.setCharacterSize(charSize);

    text.setString("");
    placeholderText.setString(placeholderTextString);

    text.setColor(textColor);

    sf::Color placeholderColor = textColor;
    placeholderColor.a -= 80;
    placeholderText.setColor(placeholderColor);

    centerOrigin(text);
    centerOrigin(placeholderText);

    text.setPosition(centerPosition);
    placeholderText.setPosition(centerPosition);

    sf::RectangleShape shape;

    if(size != sf::Vector2f(0.f, 0.f))
        shape.setSize(size);
    else
        shape.setSize(sf::Vector2f(placeholderText.getGlobalBounds().width + 20.f, placeholderText.getGlobalBounds().height + 15.f));

    shape.setFillColor(backgroundColor);
    centerOrigin(shape);
    shape.setPosition(centerPosition);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(borderLineColor);

    m_texts[name] = {shape, text, placeholderText, textColor, borderLineColor, focusedBorderLineColor, shape.getSize()};
}

void GUITextInputPool::addTextInput(std::string name, TextInput TextInput)
{
	m_texts[name] = TextInput;
}

void GUITextInputPool::removeTextInput(std::string name)
{
    auto it = m_texts.find(name);
    if(it != m_texts.end())
        m_texts.erase(it);
}

void GUITextInputPool::update()
{
    // Update hover color.
    for(auto itr(m_texts.begin()) ; itr != m_texts.end() ; ++itr)
    {
        sf::FloatRect hitbox = itr->second.shape.getGlobalBounds();
        hitbox.left += getPosition().x;
        hitbox.top += getPosition().y;
        sf::Vector2i rawMousePosition = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosition = window->mapPixelToCoords(rawMousePosition);

        if(m_useCustomView)
            mousePosition = window->mapPixelToCoords(rawMousePosition, m_customView);

        if(hitbox.contains(mousePosition) || itr->first == m_focusedTextName)
            itr->second.shape.setOutlineColor(itr->second.focusedBorderLineColor);
        else if(itr->first != m_focusedTextName) // If we are not focused and not hovered, back to basic line color.
            itr->second.shape.setOutlineColor(itr->second.borderLineColor);
    }
}

void GUITextInputPool::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        // Reset the focused text input.
        m_focusedTextName = "";

        for(std::pair<std::string, TextInput> b_pair : m_texts)
        {
            sf::FloatRect hitbox = b_pair.second.shape.getGlobalBounds();
            hitbox.left += getPosition().x;
            hitbox.top += getPosition().y;

            // Execute callback if the TextInput is clicked.
            sf::Vector2i rawMousePosition = sf::Mouse::getPosition(*window);
            sf::Vector2f mousePosition = window->mapPixelToCoords(rawMousePosition);

            if(m_useCustomView)
                mousePosition = window->mapPixelToCoords(rawMousePosition, m_customView);

            if(hitbox.contains(mousePosition))
                m_focusedTextName = b_pair.first;
        }
    }
    else if(event.type == sf::Event::TextEntered && m_focusedTextName != "")
    {
        // Backspace and delete unicode.
        if(event.text.unicode == 8 || event.text.unicode == 127)
        {
            sf::String str = m_texts[m_focusedTextName].text.getString();

            // If the string is not empty, we erase one char.
            if(str.getSize() > 0)
            {
                str.erase(str.getSize() - 1);
                m_texts[m_focusedTextName].text.setString(str);
            }

        }
        else
        {
            sf::String str = m_texts[m_focusedTextName].text.getString();
            str += event.text.unicode;
            m_texts[m_focusedTextName].text.setString(str);
        }

        // String change, origin has to be updated.
        centerOrigin(m_texts[m_focusedTextName].text);

        // Enlarge text input if necessary.
        if(m_texts[m_focusedTextName].text.getLocalBounds().width >= m_texts[m_focusedTextName].shape.getLocalBounds().width)
        {
            m_texts[m_focusedTextName].shape.setSize(sf::Vector2f(m_texts[m_focusedTextName].text.getGlobalBounds().width + 2.f, m_texts[m_focusedTextName].shape.getSize().y));
            centerOrigin(m_texts[m_focusedTextName].shape);
        }
        else if(m_texts[m_focusedTextName].text.getLocalBounds().width > m_texts[m_focusedTextName].shapeMinSize.x)
        {
            m_texts[m_focusedTextName].shape.setSize(sf::Vector2f(m_texts[m_focusedTextName].text.getGlobalBounds().width + 2.f, m_texts[m_focusedTextName].shape.getSize().y));
            centerOrigin(m_texts[m_focusedTextName].shape);
        }
        else
        {
            m_texts[m_focusedTextName].shape.setSize(m_texts[m_focusedTextName].shapeMinSize);
            centerOrigin(m_texts[m_focusedTextName].shape);
        }
    }
}

sf::String GUITextInputPool::getText(std::string name)
{
    return m_texts[name].text.getString();
}

void GUITextInputPool::setCustomView(const sf::View& v)
{
    m_useCustomView = true;
    m_customView = v;
}

void GUITextInputPool::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(std::pair<std::string, TextInput> b_pair : m_texts)
    {
        window.draw(b_pair.second.shape, states);

        // We display the text only if we are focused or we have something already written.
        if(b_pair.first == m_focusedTextName || b_pair.second.text.getString() != "")
            window.draw(b_pair.second.text, states);
        else
            window.draw(b_pair.second.placeholderText, states);
    }
}
