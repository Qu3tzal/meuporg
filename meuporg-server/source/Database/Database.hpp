#ifndef DATABASE_HPP_INCLUDED
#define DATABASE_HPP_INCLUDED

#include "../sqlite/sqlite3.h"
#include "PlayerData.hpp"

/*
    Database class.
    Encapsulates the sqlite3 database.
*/
class Database
{
    public:
        // Ctor.
        Database(std::string filepath);

        // Dtor.
        virtual ~Database();

        // Returns true if the password match.
        bool checkAccountPassword(std::string username, std::string password);

        // Returns the stats of the player.
        PlayerData getPlayerStats(std::string username);

    protected:
        // Database instance.
        sqlite3* m_db;

        // Opened flag.
        bool m_opened;
};

#endif // DATABASE_HPP_INCLUDED
