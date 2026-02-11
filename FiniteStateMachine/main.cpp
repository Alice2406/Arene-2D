#include "NPC/EnemyManager.h" 
#include "PlayerStates/Player.h"
#include "Core/CollisionManager.h"
#include "Obstacles/ObstacleManager.h"
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
    ResourceManager resourceManager;
    sf::Texture waterTexture;
    sf::Vector2u mapSizeInTiles = { 35, 20 };
    sf::Vector2u tileSize = { 63, 63 };
    sf::Vector2f worldBounds;
    ObstacleManager obstacleManager;

    worldBounds.x = mapSizeInTiles.x * tileSize.x;
    worldBounds.y = mapSizeInTiles.y * tileSize.y;
    if (!waterTexture.loadFromFile("..\\Assets\\Terrain\\Tileset\\Water.png")) return -1;
    waterTexture.setRepeated(true);
    sf::Sprite oceanSprite(waterTexture);
    oceanSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));
    oceanSprite.setPosition({ -5000.f, -5000.f });
    if (!map.load("../Assets/Levels/Level1.txt", "..\\Assets\\Terrain\\Tileset\\map.png", { 63, 63 }))
    {
        return -1;
    }
    obstacleManager.Initialize(20, worldBounds, resourceManager);
    colManager.addHurtbox(&player.hurtbox); 
    colManager.addHitbox(&player.hitbox);
    colManager.addHitbox(&player.hitbox2);

    EnemyManager enemyManager;

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
        enemyManager.HandleWaves(worldBounds);
        player.Update(window, dt, worldBounds);
        enemyManager.Update(dt, player, worldBounds);
        window.draw(oceanSprite);
        window.draw(map);
        obstacleManager.Draw(window);
        enemyManager.Draw(window);

        window.draw(player.getSprite());

        player.hurtbox.debugDraw(window);
        player.hitbox.debugDraw(window);
        player.hitbox2.debugDraw(window);
        window.display();
    }

    return 0;
}

/*
* menu fin
* collision ennemis
* obstacles statiques
*/