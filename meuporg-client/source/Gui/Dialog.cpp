#include "Dialog.hpp"

Dialog::Dialog(kantan::FontHolder* fonts) : arrow("->")
    , itr(0)
    , choice(nullptr)
    , timer(sf::Time::Zero)
    , drawArrow(true)
    , finished(false)
    , choiceStep(false)
{
    this->fonts = fonts;
}

Dialog::~Dialog()
{
    //dtor
    delete choice;
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
    if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Return)
    {
        if(!choiceStep)
            next();
        else
        {
            int key = choice->possibilities.at(choiceTexts[itr].getString());
            if(key == -1)
                finished = true;
            else
            {
                choice->callback(key);
                finished = true;
            }
        }
    }

    if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Up)
    {
        if(choiceStep)
        {
            if(itr > 0)
            {
                itr--;
                nextPageText.setPosition(nextPageText.getPosition().x, choiceTexts[itr].getPosition().y);
            }
        }
    }

    if(e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Down)
    {
        if(choiceStep)
        {
            if(itr < choiceTexts.size() - 1)
            {
                itr++;
                nextPageText.setPosition(nextPageText.getPosition().x, choiceTexts[itr].getPosition().y);
            }
        }
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
        if(choice != nullptr)
        {
            choiceStep = true;
            initChoice();
        }
        else
            finished = true;
    }
}

void Dialog::initChoice()
{
    int i = 0;
    for(auto itr = choice->possibilities.begin(); itr != choice->possibilities.end(); itr++)
    {
        sf::Text text;
        text.setPosition(20, 10 + i * 25);
        text.setFont(fonts->get(ResourceId::MONOF_56));
        text.setCharacterSize(16);
        text.setColor(sf::Color::White);
        text.setString(itr->first);

        choiceTexts.push_back(text);
        i++;
    }
    nextPageText.setPosition(0, 10);
    itr = 0;
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
    }

    unsigned int nb = 0;
    for(unsigned int j = 0 ; j < str.length(); j++)
    {
        if(str.at(j) == '\n')
        {
            nb++;
            if(nb == maxLine)
            {
                texts.push_back(str.substr(0, j + 1));
                str.erase(0, j + 1);
                nb = 0;
                j = 0;
            }

        }
    }
    if(str.length() > 0 )
    {
        texts.push_back(str);
    }
    next();

}

DialogChoice* Dialog::addChoice()
{
    choice = new DialogChoice();
    return choice;
}

bool Dialog::isFinished()
{
    return finished;
}

void Dialog::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    window.draw(background, states);
    if(!choiceStep)
        window.draw(text, states);
    else
    {
        for(sf::Text t : choiceTexts)
        {
            window.draw(t, states);
        }
    }
    if(drawArrow)
        window.draw(nextPageText, states);
}
