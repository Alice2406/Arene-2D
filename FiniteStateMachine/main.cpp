#include "NPC/Berserker.h"
#include "NPC/Sniper.h"
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
    berserker.Init();
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
        berserker.Update();
        sniper.Update();
        player.Update(window);
        window.draw(player.getShape());
        window.draw(berserker.getShape());
        window.draw(sniper.getShape());
        window.display();
    }
}
