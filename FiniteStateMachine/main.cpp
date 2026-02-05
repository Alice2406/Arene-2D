#include "StateMachine/NPC.h"
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
    Npc npc;

    npc.Init();
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        npc.context.deltaTime = dt;
        npc.context.playerPos = player.getPosition();
        npc.Update();
        player.Update(window);
        window.draw(player.getShape());
        window.draw(npc.getShape());
        window.display();
    }
}
