#ifndef PLAYERSTATS_HPP_INCLUDED
#define PLAYERSTATS_HPP_INCLUDED

/*
    Data of a player in the database.
*/
struct PlayerData
{
    int dbid = -1;
    std::string username = "";
    std::string hashedPassword = "";

    int worldId = -1;
    float positionX = 0.f;
    float positionY = 0.f;

    float hp = 1.f;
    float maxhp = 1.f;
    float strength = 0.f;
    float agility = 0.f;
    float resistance = 0.f;

    float xp = 0.f;
    float level = 0.f;
};

#endif // PLAYERSTATS_HPP_INCLUDED
