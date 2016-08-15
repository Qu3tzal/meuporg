#ifndef DIALOGMANAGER_HPP
#define DIALOGMANAGER_HPP


#include <stack>
#include <SFML/System.hpp>

#include "Dialog.hpp"
#include "../ResourceHolder.hpp"

class DialogManager : public sf::Drawable, public sf::Transformable
{
    public:
        DialogManager(kantan::FontHolder* fonts);
        virtual ~DialogManager();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        Dialog* createDialog();


    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        std::stack<Dialog*> dialogs;

        kantan::FontHolder* fonts;

    private:
};

#endif // DIALOGMANAGER_HPP
