#include "NPC/EnemyManager.h" 
#include "PlayerStates/Player.h"
#include "Core/CollisionManager.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "Arene 2D");
    sf::View camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(1900.f, 800.f));
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Clock clock;
    TileMap map;
    Player player;
    CollisionManager colManager;

    if (!map.load("../Assets/Levels/Level1.txt", "..\\Assets\\Terrain\\Tileset\\map.png", { 64, 64 }))
    {
        return -1;
    }
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
        camera.setCenter(player.getPosition());
        window.clear();
        window.setView(camera);
        colManager.checkCollisions();
        player.Update(window, dt);
        enemyManager.Update(dt, player);
        window.draw(map);
        enemyManager.Draw(window);

        window.draw(player.getSprite());

        player.hurtbox.debugDraw(window);
        player.hitbox.debugDraw(window);
        player.hitbox2.debugDraw(window);
        window.display();
    }

    return 0;
}