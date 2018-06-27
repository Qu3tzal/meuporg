#ifndef MISSION_HPP
#define MISSION_HPP

#include <string>
#include <vector>
#include <SFML/System.hpp>

class Mission
{
    public:
        Mission(sf::Uint64 missionId);

        virtual ~Mission();

        void init();

        sf::Uint64 getMissionId() const;

        void addText(std::string str);

        std::string getText() const;

        void nextText();

        void resetIndex();

    protected:

        sf::Uint64 missionId;

        std::vector<std::string> text;

        // the text index
        sf::Uint64 index;


    private:
};

#endif // MISSION_HPP
