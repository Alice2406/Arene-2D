#include "NPC/Berserker.h"
#include "NPC/Sniper.h"
#include "NPC/Tank.h"
#include "Player.h"
#include "Time.h"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "SFML works!");
    window.setFramerateLimit(60);
    srand(time(NULL));
    sf::Clock clock;
    Player player;
    Berserker berserker;
    Sniper sniper;
    Tank tank;

    berserker.Init();
    tank.Init();
    sniper.Init();

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        berserker.context.deltaTime = dt;
        berserker.context.playerPos = player.getPosition();
        sniper.context.deltaTime = dt;
        sniper.context.playerPos = player.getPosition();
        tank.context.deltaTime = dt;
        tank.context.playerPos = player.getPosition();

        berserker.Update();
        sniper.Update();
        tank.Update();
        player.Update(window);

        window.draw(player.getShape());
        window.draw(berserker.getShape());
        window.draw(sniper.getShape());
        window.draw(tank.getShape());
        window.display();
    }
}
