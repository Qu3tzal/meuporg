#include "Mission.hpp"

Mission::Mission(sf::Uint64 id)
{
    this->missionId = id;
}

Mission::~Mission()
{
    //dtor
}

void Mission::init()
{
    switch(missionId)
    {
    case 0 :
        addText("Bonjour, Je m'appele Pnice et je suis là pour te la mettre !");
        addText("J'ai une mission à te proposer ! Serait tu capables d'enculer l'enculeur de mouche ?");
    }
}

void Mission::addText(std::string str)
{
    text.push_back(str);
}

sf::Uint64 Mission::getMissionId() const
{
    return this->missionId;
}

std::string Mission::getText() const
{
    return text[index];
}

void Mission::nextText()
{
    if(index <= text.size() - 1)
    {
        index++;
    }
}

void Mission::resetIndex()
{
    index = 0;
}
