#include "NpcStates/NPC.h"
#include "PlayerStates/Player.h"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "SFML works!");
    window.setFramerateLimit(60);
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
        player.Update(window, dt);
        window.draw(player.getSprite());
        window.draw(npc.getShape());
        window.display();
    }
}
