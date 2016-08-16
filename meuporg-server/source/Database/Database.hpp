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

        // Creates an account.
        void createAccount(const std::string& username, const std::string& password = "");

        // Returns true if the account exists.
        bool checkAccountExists(const std::string& username);

        // Returns true if the password match.
        bool checkAccountPassword(const std::string& username, const std::string& password);

        // Returns the stats of the player.
        PlayerData getPlayerStats(const std::string& username);

        // Writes the stats of the player.
        /// /!\ Except the username and hashed password !
        void writePlayerStats(const PlayerData& playerData);

    protected:
        // Database instance.
        sqlite3* m_db;

        // Opened flag.
        bool m_opened;
};

#endif // DATABASE_HPP_INCLUDED
