#include <iostream>
#include <thread>
#include <SFML/Network.hpp>

#include "ServerConfiguration.hpp"
#include "Server/Server.hpp"
#include "InformationServer/InformationServer.hpp"
#include "Multithreading.hpp"

int informationServer_main(Server* server)
{
    InformationServer informationServer(server);
    informationServer.init();

    sf::Clock serverclock;
    while(informationServer.isRunning() && server->isRunning())
    {
        informationServer.update(serverclock.restart());
    }

    return 0;
}

int main()
{
    std::cout << "\t-*- #meuporg -*-" << std::endl;
    std::cout << "Version " << ServerConfiguration::Version << " (" << ServerConfiguration::TickPerSec << " tick/sec)." << std::endl;

    Server server;

    // Launch the information server.
    std::thread informationServer_thread(&informationServer_main, &server);

    /*
        Game server.
    */
    server.init();

    sf::Clock serverclock;
    sf::Time elapsed(sf::Time::Zero);
    sf::Time elapsedSinceLastLogin(sf::Time::Zero);
    sf::Time performancesTimer(sf::Time::Zero);
    unsigned int ticks(0);

    while(server.isRunning())
    {
        sf::Time dt = serverclock.restart();
        elapsed += dt;
        elapsedSinceLastLogin += dt;
        performancesTimer += dt;

        while(elapsedSinceLastLogin >= ServerConfiguration::LoginTicktime)
        {
            elapsedSinceLastLogin -= ServerConfiguration::LoginTicktime;

            server.login(ServerConfiguration::LoginTicktime);
        }

        while(elapsed >= ServerConfiguration::Ticktime)
        {
            elapsed -= ServerConfiguration::Ticktime;

            server.receiveInput();
            server.update(ServerConfiguration::Ticktime);
            server.sendUpdate();

            ticks++;
            if(performancesTimer >= sf::seconds(1.f))
            {
                if(ticks < ServerConfiguration::TickPerSec)
                    std::cout << "[STATS] " << ticks << " tick/sec (goal: " << ServerConfiguration::TickPerSec << " tick/sec)." << std::endl;
                performancesTimer = sf::Time::Zero;
                ticks = 0;
            }
        }
    }

    // Stop all threads.
    informationServer_thread.join();

    std::cout << "\tGood bye !" << std::endl;

    return 0;
}
