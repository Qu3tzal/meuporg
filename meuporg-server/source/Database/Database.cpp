#include "Database.hpp"

Database::Database(std::string filepath)
{
    m_opened = false;

    // Check error.
    m_lastError = sqlite3_open(filepath.c_str(), &m_db);

    if(m_lastError == SQLITE_OK)
    {
        m_opened = true;
    }
}

Database::~Database()
{
    if(m_opened)
        sqlite3_close(m_db);
}

int Database::getLastError() const
{
    return m_lastError;
}

void Database::createAccount(const std::string& username, const std::string& password)
{
    // Prepare statement.
    std::string statementString("INSERT INTO `players` (username, password, hp, maxhp, strength, agility, resistance, xp, level) VALUES(:username, :password, :hp, :maxhp, :strength, :agility, :resistance, :xp, :level)");

    sqlite3_stmt* statement;
    m_lastError = sqlite3_prepare(m_db, statementString.c_str(), statementString.size(), &statement, nullptr);

    if(m_lastError != SQLITE_OK)
        return;

    // Bind parameter.
    int parameterIndex = sqlite3_bind_parameter_index(statement, ":username");
    sqlite3_bind_text(statement, parameterIndex, username.c_str(), username.size(), nullptr);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":password");
    sqlite3_bind_text(statement, parameterIndex, password.c_str(), password.size(), nullptr);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":hp");
    sqlite3_bind_double(statement, parameterIndex, 100.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":maxhp");
    sqlite3_bind_double(statement, parameterIndex, 100.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":strength");
    sqlite3_bind_double(statement, parameterIndex, 0.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":agility");
    sqlite3_bind_double(statement, parameterIndex, 0.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":resistance");
    sqlite3_bind_double(statement, parameterIndex, 0.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":xp");
    sqlite3_bind_double(statement, parameterIndex, 0.f);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":level");
    sqlite3_bind_double(statement, parameterIndex, 0.f);


    // Execute.
    while(true)
    {
        int status = sqlite3_step(statement);

        if(status == SQLITE_BUSY)
            continue;

        return;
    }
}

bool Database::checkAccountExists(const std::string& username)
{
    // Prepare statement.
    std::string statementString("SELECT id FROM `players` WHERE username=:username");

    sqlite3_stmt* statement;
    m_lastError = sqlite3_prepare(m_db, statementString.c_str(), statementString.size(), &statement, nullptr);

    if(m_lastError != SQLITE_OK)
        return false;

    // Bind parameter.
    int usernameParameterIndex = sqlite3_bind_parameter_index(statement, ":username");
    sqlite3_bind_text(statement, usernameParameterIndex, username.c_str(), username.size(), nullptr);

    // Execute.
    while(true)
    {
        int status = sqlite3_step(statement);

        if(status == SQLITE_BUSY)
            continue;

        bool result = (status == SQLITE_ROW);

        // Free.
        sqlite3_finalize(statement);
        return result;
    }
}

bool Database::checkAccountPassword(const std::string& username, const std::string& password)
{
    // Prepare statement.
    std::string statementString("SELECT id FROM `players` WHERE username=:username AND hashedPassword=:hashedPassword");

    sqlite3_stmt* statement;
    m_lastError = sqlite3_prepare(m_db, statementString.c_str(), statementString.size(), &statement, nullptr);

    if(m_lastError != SQLITE_OK)
        return false;

    std::string hashedPassword(""); /// /!\ Hash the password.

    // Bind parameters.
    int usernameParameterIndex = sqlite3_bind_parameter_index(statement, ":username");
    int hashedPasswordParameterIndex = sqlite3_bind_parameter_index(statement, ":hashedPassword");
    sqlite3_bind_text(statement, usernameParameterIndex, username.c_str(), username.size(), nullptr);
    sqlite3_bind_text(statement, hashedPasswordParameterIndex, hashedPassword.c_str(), hashedPassword.size(), nullptr);

    // Execute.
    while(true)
    {
        int status = sqlite3_step(statement);

        if(status == SQLITE_BUSY)
            continue;

        bool result = (status == SQLITE_ROW);

        // Free.
        sqlite3_finalize(statement);
        return result;
    }
}

PlayerData Database::getPlayerData(const std::string& username)
{
    // Prepare statement.
    std::string statementString("SELECT * FROM `players` WHERE username=:username");

    sqlite3_stmt* statement;
    m_lastError = sqlite3_prepare(m_db, statementString.c_str(), statementString.size(), &statement, nullptr);

    if(m_lastError != SQLITE_OK)
        return PlayerData();

    // Bind parameters.
    int usernameParameterIndex = sqlite3_bind_parameter_index(statement, ":username");
    sqlite3_bind_text(statement, usernameParameterIndex, username.c_str(), username.size(), nullptr);

    // Execute.
    while(true)
    {
        int status = sqlite3_step(statement);

        if(status == SQLITE_BUSY)
            continue;

        break;
    }

    PlayerData playerData;

    playerData.dbid = sqlite3_column_int(statement, 0);

    const unsigned char* cuc_string_username = sqlite3_column_text(statement, 1);
    const char* cc_string_username = reinterpret_cast<const char*>(cuc_string_username);

    try
    {
        playerData.username = std::string(cc_string_username);
    }
    catch(std::exception& e)
    {
        playerData.username = "";
    }

    const unsigned char* cuc_string_hashedPassword = sqlite3_column_text(statement, 2);
    const char* cc_string_hashedPassword = reinterpret_cast<const char*>(cuc_string_hashedPassword);

    try
    {
        playerData.hashedPassword = std::string(cc_string_hashedPassword);
    }
    catch(std::exception& e)
    {
        playerData.hashedPassword = "";
    }


    playerData.worldId = sqlite3_column_int(statement, 3);
    playerData.positionX = sqlite3_column_double(statement, 4);
    playerData.positionY = sqlite3_column_double(statement, 5);

    playerData.hp = sqlite3_column_double(statement, 6);
    playerData.maxhp = sqlite3_column_double(statement, 7);
    playerData.strength = sqlite3_column_double(statement, 8);
    playerData.agility = sqlite3_column_double(statement, 9);
    playerData.resistance = sqlite3_column_double(statement, 10);

    playerData.xp = sqlite3_column_double(statement, 11);
    playerData.level = sqlite3_column_double(statement, 12);

    // Free.
    sqlite3_finalize(statement);

    return playerData;
}

void Database::writePlayerData(const PlayerData& playerData)
{
    // Prepare statement.
    std::string statementString("UPDATE `players` SET worldId=:worldId, positionX=:positionX, positionY=:positionY, hp=:hp, maxhp=:maxhp, strength=:strength, agility=:agility, resistance=:resistance, xp=:xp, level=:level WHERE id=:dbid");

    sqlite3_stmt* statement;
    m_lastError = sqlite3_prepare(m_db, statementString.c_str(), statementString.size(), &statement, nullptr);

    if(m_lastError != SQLITE_OK)
        return;

    // Bind parameters.
    int parameterIndex = sqlite3_bind_parameter_index(statement, ":dbid");
    sqlite3_bind_int(statement, parameterIndex, playerData.dbid);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":worldId");
    sqlite3_bind_int(statement, parameterIndex, playerData.worldId);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":positionX");
    sqlite3_bind_double(statement, parameterIndex, playerData.positionX);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":positionY");
    sqlite3_bind_double(statement, parameterIndex, playerData.positionY);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":hp");
    sqlite3_bind_double(statement, parameterIndex, playerData.hp);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":maxhp");
    sqlite3_bind_double(statement, parameterIndex, playerData.maxhp);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":strength");
    sqlite3_bind_double(statement, parameterIndex, playerData.strength);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":agility");
    sqlite3_bind_double(statement, parameterIndex, playerData.agility);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":resistance");
    sqlite3_bind_double(statement, parameterIndex, playerData.resistance);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":xp");
    sqlite3_bind_double(statement, parameterIndex, playerData.xp);

    parameterIndex = sqlite3_bind_parameter_index(statement, ":level");
    sqlite3_bind_double(statement, parameterIndex, playerData.level);

    // Execute.
    while(true)
    {
        int status = sqlite3_step(statement);

        if(status == SQLITE_BUSY)
            continue;

        break;
    }

    // Free.
    sqlite3_finalize(statement);
}
