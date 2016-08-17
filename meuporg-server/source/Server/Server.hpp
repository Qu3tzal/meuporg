#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <exception>
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <map>

#include <SFML/Network.hpp>

#include "../Accounts.hpp"
#include "../Database/Database.hpp"
#include "../Multithreading.hpp"
#include "../NetworkValues.hpp"
#include "../ServerConfiguration.hpp"
#include "../LoginServer/LoginServer.hpp"
#include "../RandomNumberGenerator/RandomNumberGenerator.hpp"
#include "../World/World.hpp"

#include "../Kantan-2/kantan.hpp"

/*
    Server class.
    This class manages the main functions of the server.
*/
class Server
{
    public:
        // Pending socket structure. Holds a pending socket and its timeout together.
        struct PendingSocket
        {
            std::shared_ptr<sf::TcpSocket> tcpSocket;
            sf::Time timeout = sf::Time::Zero;
        };

    public:
        // Constructor.
        Server();

        // Destructor.
        virtual ~Server();

        // Inits the server.
        void init();

        // Returns true if the server is running, false otherwise.
        bool isRunning() const;

        // Logs in the new players.
        void login(sf::Time dt);

        // Receives the input from the clients.
        void receiveInput();

        // Updates the server.
        void update(sf::Time dt);

        // Sends the update to the clients.
        void sendUpdate();

        // Returns the number of players currently online.
        unsigned int getNumberOfPlayers() const;

        // Return the maximum players capacity of the server.
        unsigned int getMaximumPlayersCapacity() const;

        // Returns the list of clients.
        std::vector<Client*>* getClients();

        // Returns the list of accounts.
        std::map<std::string, Account*>* getAccounts();

        // Shuts down the server.
        void shutdown();

    protected:
        friend World;
        friend LoginServer;

        // Disconnects the player for the given reason.
        void disconnectPlayer(std::string username, std::string reason);

        // Updates the number of players.
        void updateNumberOfPlayers();

        // Updates the timeout of the players.
        void updateTimeoutPlayers(sf::Time dt);

        // Receives the input from the clients TCP sockets.
        void receiveInputThroughTCP();

        // Receives the input by the UDP socket.
        void receiveInputThroughUDP();

        // Sends the chat message.
        void sendChatMessage(std::string username, std::string channel, std::string message);

        // Notifies everyone the player connected.
        void notifyPlayerConnected(std::string username);

        // Notifies everyone the player disconnected.
        void notifyPlayerDisconnected(std::string username);

        // Notifies everyone the entity has been removed.
        void notifyEntityRemoved(unsigned int entityId);

        // Returns true if the given string is a chat command.
        bool isChatCommand(std::string command);

        // Switch a client from a world to another.
        void switchClientToWorld(Client* client, int worldId);

        // Returns true if the account exists.
        bool checkAccountExists(const std::string& username);

        // Create an account with default stats.
        void createAccount(const std::string& username, const std::string& password);

        // Returns the player data.
        PlayerData getPlayerData(const std::string& username);

        // Writes the player data.
        void writePlayerData(const PlayerData& playerData);

    protected:
        // Database.
        Database m_database;

        // Number of players connected and maximum number of players.
        unsigned int m_numberOfPlayers;
        unsigned int m_maximumPlayersCapacity;

        // List of the clients.
        std::vector<Client*> m_clients;

        // List of the accounts (indexed by the username).
        std::map<std::string, Account*> m_accounts;

        // The login server.
        LoginServer m_loginServer;

        // The game TCP listener.
        sf::TcpListener m_gameTcpListener;

        // The game UDP socket.
        sf::UdpSocket m_gameUdpSocket;

        // Pending TCP connections.
        std::vector<PendingSocket*> m_pendingTcpSockets;

        // Chat log : (username, message).
        std::vector<std::pair<std::string, std::string>> m_chatLog;

        // Multithreading worlds.
        std::vector<World*> m_worlds;
};

#endif // SERVER_HPP_INCLUDED
