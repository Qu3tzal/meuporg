#include "Dialog.hpp"

Dialog::Dialog(kantan::FontHolder* fonts) : arrow("->")
    , itr(0)
    , timer(sf::Time::Zero)
    , drawArrow(true)
    , finished(false)
{
    this->fonts = fonts;
}

Dialog::~Dialog()
{
    //dtor
}

void Dialog::init()
{
    background.setFillColor(sf::Color(60, 60, 60, 60));
    background.setSize(sf::Vector2f(350, 75));

    text.setPosition(10, 10);
    text.setFont(fonts->get(ResourceId::MONOF_56));
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);

    nextPageText.setPosition(328, 55);
    nextPageText.setFont(fonts->get(ResourceId::MONOF_56));
    nextPageText.setCharacterSize(16);
    nextPageText.setColor(sf::Color::White);
    nextPageText.setString(arrow);
}

void Dialog::update(sf::Time dt)
{
    timer += dt;
    if(timer.asSeconds() >= 0.5f)
    {
        drawArrow = !drawArrow;
        timer = sf::Time::Zero;
    }
}

void Dialog::handleEvent(sf::Event e)
{
    if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return)
    {
        next();
    }
}

void Dialog::next()
{
    if(itr < texts.size())
    {
        text.setString(texts[itr]);
        itr++;
    }
    else if(itr == texts.size())
    {
        finished = true;
    }
}

void Dialog::setText(std::string str)
{
    unsigned int maxSize(40);
    unsigned int maxLine(3);

    if(str.length() >= maxSize)
    {

        for(unsigned int j = 1 ; j <= (unsigned int)(str.length()/maxSize); j++)
        {
            str.insert(j * maxSize , "\n");
        }

        unsigned int last = 0;
        for(unsigned int i = 0; i < str.length(); i++)
        {
            if(i >= maxLine * maxSize)
            {
                texts.push_back(str.substr(last, maxLine * maxSize));
                last = maxLine * maxSize;
            }
        }
        texts.push_back(str.substr(last, str.length() - last));

    }
    next();

}

bool Dialog::isFinished()
{
    return finished;
}

void Dialog::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background, states);
    window.draw(text, states);
    if(drawArrow)
        window.draw(nextPageText, states);
}
