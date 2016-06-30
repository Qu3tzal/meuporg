
#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>
#include <Game.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    const float TickRate = 1/60.f;
    const sf::Time TickRateTime = sf::seconds(TickRate);

    const int frameRateLock = 60;
    const float frameRate = 1.f/frameRateLock;
    const sf::Time frameRateTime = sf::seconds(frameRate);

    int ticks = 0;
    int frames = 0;

    const std::string TITLE  = "MMPROPPPG";

    sf::RenderWindow window(sf::VideoMode(1280, 800), TITLE);

    Game game(&window);
    game.init();

    sf::Clock clientClock;
    sf::Time elapsed;
    sf::Time frame;
    sf::Time dt;
    sf::Time fpsTimer;

    // Start the game loop
    while (window.isOpen())
    {
        if(!game.isRunning())
            window.close();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            game.EventHandle(event);
        }
        dt = clientClock.restart();
        elapsed += dt;

        if(elapsed.asSeconds() > TickRate)
        {
            elapsed -= TickRateTime;
            game.update(TickRateTime);
            ticks++;
        }

        frame += dt;

        if(frame.asSeconds() > frameRate)
        {
            frame -= frameRateTime;
            game.render(&window);
            frames++;
        }

        fpsTimer += dt;

        if(fpsTimer.asSeconds() > 1)
        {
            std::stringstream ss;
            ss << ticks << " " << frames;
            std::string strt, strf;
            ss >> strt >> strf;
            fpsTimer -=  sf::seconds(1.f);
            window.setTitle(TITLE + " ticks : " + strt + " , FPS : " + strf);
            ticks = 0;
            frames = 0;
        }
    }

    std::cout << "Press enter to quit..." << std::endl;
    std::cin.get();
    std::cin.get();

    return 0;
}
