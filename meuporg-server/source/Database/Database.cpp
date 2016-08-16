#include "Database.hpp"

Database::Database(std::string filepath)
{
    m_opened = false;

    // Check error.
    int error = sqlite3_open(filepath.c_str(), m_db);

    if(error == SQLITE_OK)
    {
        m_opened = true;
    }
}

Database::~Database()
{
    if(m_opened)
        sqlite3_close(m_db);
}

bool Database::checkAccountPassword(std::string username, std::string password)
{

}

PlayerData Database::getPlayerStats(std::string username)
{

}
