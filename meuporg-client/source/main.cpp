#include <iostream>
#include <SFML/Network.hpp>
#include <Game.hpp>
int main()
{
    const float TickRate = 1/60.f;
    const sf::Time TickRateTime = sf::seconds(TickRate);
    Game game;
    game.init();

    sf::Clock clientClock;
    sf::Time elapsed;

     while(game.isRunning())
    {
        elapsed += clientClock.restart();

        while(elapsed >= TickRateTime)
        {
            elapsed -= TickRateTime;

            game.update(elapsed);
        }
    }

    return 0;
}
