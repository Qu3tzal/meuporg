#ifndef MISSION_HPP
#define MISSION_HPP

#include <string>
#include <vector>

class Mission
{
    public:
        Mission(unsigned int missionId);

        virtual ~Mission();

        void init();

        unsigned int getMissionId() const;

        void addText(std::string str);

        std::string getText() const;

        void nextText();

        void resetIndex();

    protected:

        unsigned int missionId;

        std::vector<std::string> text;

        // the text index
        unsigned int index;


    private:
};

#endif // MISSION_HPP
