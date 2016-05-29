#include <iostream>
#include <SFML/Network.hpp>

#include "ServerConfiguration.hpp"
#include "Server/Server.hpp"
#include "InformationServer/InformationServer.hpp"

int informationServer_main(Server* server)
{
    InformationServer informationServer(server);
    informationServer.init();

    sf::Clock serverclock;
    while(informationServer.isRunning())
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
    sf::Thread informationServer_thread(&informationServer_main, &server);
    informationServer_thread.launch();

    /*
        Game server.
    */
    server.init();

    sf::Clock serverclock;
    sf::Time elapsed(sf::Time::Zero);

    while(server.isRunning())
    {
        elapsed += serverclock.restart();

        while(elapsed >= ServerConfiguration::Ticktime)
        {
            elapsed -= ServerConfiguration::Ticktime;

            server.login(ServerConfiguration::Ticktime);
            server.receiveInput();
            server.update(ServerConfiguration::Ticktime);
            server.sendUpdate();
        }
    }

    // Stop the information server.
    informationServer_thread.terminate();

    return 0;
}
