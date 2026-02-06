#include "NPC/EnemyManager.h" 
#include "NpcStates/NPC.h"
#include "PlayerStates/Player.h"
#include "CollisionManager.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Arene 2D");
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Clock clock;
    Player player;
    CollisionManager colManager;

    colManager.addHurtbox(&player.hurtbox);
    colManager.addHitbox(&player.hitbox);
    colManager.addHitbox(&player.hitbox2);

    EnemyManager enemyManager;

    enemyManager.SpawnTank(TankSkin::TURTLE, { -10.f, -10.f });
    enemyManager.SpawnTank(TankSkin::PANDA, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::THIEF, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::LANCER, { -10.f, -10.f });
    enemyManager.SpawnSniper(SniperSkin::GNOLL, { -10.f, -10.f });
    enemyManager.SpawnSniper(SniperSkin::SHAMAN, { -10.f, -10.f });

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        colManager.CheckCollisions();
        player.Update(window, dt);
        enemyManager.Update(dt, player.getPosition());
        enemyManager.Draw(window);

        window.draw(player.getSprite());

        player.hurtbox.debugDraw(window);
        player.hitbox.debugDraw(window);
        player.hitbox2.debugDraw(window);
        window.display();
    }

    return 0;
}