#include <iostream>
#include <sstream>
#include <SFML/Network.hpp>
#include <Game.hpp>
#include <SFML/Graphics.hpp>
int main()
{
    const float TickRate = 1/60.f;
    const sf::Time TickRateTime = sf::seconds(TickRate);
    int ticks = 0;
    int frames = 0;

    const std::string TITLE  = "MMPROPPPG";

    sf::RenderWindow window(sf::VideoMode(800, 600), TITLE);

    Game game;
    game.init();

    sf::Clock clientClock;
    sf::Time elapsed;
    sf::Time dt;
    sf::Time time;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dt = clientClock.restart();
        elapsed += dt;

        if(elapsed.asSeconds() > TickRate) {
            elapsed -= TickRateTime;
            game.update(TickRateTime);
            ticks++;
        }

        game.render(window);
        frames++;

        time += dt;

        if(time.asSeconds() > 1)
        {
            std::stringstream ss;
            ss << ticks << " " << frames;
            std::string strt, strf;
            ss >> strt >> strf;
            time -=  sf::seconds(1.f);
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
