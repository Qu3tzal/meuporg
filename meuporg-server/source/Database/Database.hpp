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

        // Returns the last error code.
        int getLastError() const;

        // Creates an account.
        void createAccount(const std::string& username, const std::string& password = "");

        // Returns true if the account exists.
        bool checkAccountExists(const std::string& username);

        // Returns true if the password match.
        bool checkAccountPassword(const std::string& username, const std::string& password);

        // Returns the stats of the player.
        PlayerData getPlayerData(const std::string& username);

        // Writes the stats of the player.
        /// /!\ Except the username and hashed password !
        void writePlayerData(const PlayerData& playerData);

    protected:
        // Database instance.
        sqlite3* m_db;

        // Opened flag.
        bool m_opened;

        // Last error.
        int m_lastError;
};

#endif // DATABASE_HPP_INCLUDED
