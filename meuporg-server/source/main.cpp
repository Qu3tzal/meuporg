#include <iostream>
#include <SFML/Network.hpp>

#include "ServerConfiguration.hpp"
#include "Server/Server.hpp"

int main()
{
    std::cout << "\t-*- #meuporg -*-" << std::endl;
    std::cout << "Version " << ServerConfiguration::Version << "(" << ServerConfiguration::TickPerSec << " tick/sec)." << std::endl;

    Server server;
    server.init();

    sf::Clock serverclock;
    sf::Time elapsed(sf::Time::Zero);

    while(server.isRunning())
    {
        elapsed += serverclock.restart();

        while(elapsed >= ServerConfiguration::Ticktime)
        {
            elapsed -= ServerConfiguration::Ticktime;

            server.receiveInput();
            server.update(ServerConfiguration::Ticktime);
            server.sendUpdate();
        }
    }

    return 0;
}
