#include "DialogManager.hpp"

DialogManager::DialogManager(kantan::FontHolder* fonts)
{
    this->fonts = fonts;
}

DialogManager::~DialogManager()
{
    //dtor
}

void DialogManager::init()
{

}

void DialogManager::update(sf::Time dt)
{
    if(!dialogs.empty())
    {
        dialogs.top()->update(dt);

        if(dialogs.top()->isFinished())
        {
            delete dialogs.top();
            dialogs.pop();
        }
    }

}

void DialogManager::handleEvent(sf::Event e)
{
    if(!dialogs.empty())
        dialogs.top()->handleEvent(e);
}

Dialog* DialogManager::createDialog()
{
    Dialog* dialog = new Dialog(fonts);
    dialog->init();
    dialogs.push(dialog);

    return dialog;
}

void DialogManager::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if(!dialogs.empty())
        window.draw(*dialogs.top(), states);
}

