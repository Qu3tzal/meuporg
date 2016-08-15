#include "Dialog.hpp"

Dialog::Dialog(kantan::FontHolder* fonts) : arrow("->")
    ,itr(0)
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
    background.setSize(sf::Vector2f(100, 50));

    text.setFont(fonts->get(ResourceId::MONOF_56));
    text.setCharacterSize(16);
    text.setColor(sf::Color::White);
}

void Dialog::update(sf::Time dt)
{

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
    if(itr == texts.size()-1)
    {

    }
}

void Dialog::setText(std::string str)
{
    unsigned int maxSize(40);
    unsigned int maxLine(3);

    if(str.length() >= maxSize)
    {
        unsigned int nb = 1;
        unsigned int last = 0;
        for(unsigned int j = 1 ; j <= (unsigned int)(str.length()/maxSize); j++)
        {
            str.insert(j * maxSize , "\n");
            nb++;
            if(nb == maxLine)
            {
                texts.push_back(str.substr((j - 1) * maxSize, (j * maxSize + 1) - ((j - 1) * maxSize)));
                nb = 0;
                last = j * maxSize + 1;
            }
        }
        texts.push_back(str.substr(last, str.size() - last));

    }
    next();

}

void Dialog::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background, states);
    window.draw(text, states);
}
