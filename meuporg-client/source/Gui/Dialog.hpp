#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "../ResourceHolder.hpp"
#include "../ResourceId.hpp"

struct DialogChoice
{
    std::map<int, std::string> possibilities;
    std::function<void(int)> callback;
};

class Dialog : public sf::Drawable, public sf::Transformable
{
    public:
        Dialog(kantan::FontHolder* fonts);

        virtual ~Dialog();

        void init();

        void update(sf::Time dt);

        void handleEvent(sf::Event e);

        void setText(std::string str);

        void setChoice(DialogChoice choice);

        bool isFinished();

    protected:

        virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const;

        std::string arrow;

    private:

        kantan::FontHolder* fonts;

        sf::RectangleShape background;

        sf::Text text;

        sf::Text nextPageText;

        void next();

        unsigned int itr;

        std::vector<std::string> texts;

        DialogChoice choice;

        sf::Time timer;

        bool drawArrow;

        bool finished;
};

#endif // DIALOG_HPP
