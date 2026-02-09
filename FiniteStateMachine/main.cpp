#include "NpcStates/NPC.h"
#include "PlayerStates/Player.h"
#include "CollisionManager.h"
#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Arene 2D");
    window.setFramerateLimit(60);
    sf::Clock clock;
    Player player;
    Npc npc;
    CollisionManager colManager;

    colManager.addHurtbox(&player.hurtbox);
    colManager.addHitbox(&player.hitbox);
    colManager.addHitbox(&player.hitbox2);

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
        colManager.checkCollisions();
        player.Update(window, dt);
        window.draw(player.getSprite());
        /*window.draw(npc.getShape());*/
        player.hurtbox.debugDraw(window);
        player.hitbox.debugDraw(window);
        player.hitbox2.debugDraw(window);
        window.display();
    }
}
