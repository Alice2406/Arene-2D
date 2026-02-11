#include "NPC/EnemyManager.h" 
#include "PlayerStates/Player.h"
#include "Core/CollisionManager.h"
#include "Obstacles/ObstacleManager.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"

//void SpawnRandomObstacles(int count, sf::Vector2f mapSize)
//{
//    for (int i = 0; i < count; i++)
//    {
//        // Position aléatoire
//        float x = rand() % (int)mapSize.x;
//        float y = rand() % (int)mapSize.y;
//
//        // Choix du type (0 à 4)
//        int randomType = rand() % 5;
//        ObstacleType type;
//        sf::Texture* texture = nullptr; // Pointeur vers la texture à utiliser
//
//        switch (randomType) {
//        case 0:
//            type = ObstacleType::ROCK;
//            texture = &rm.GetTexture("rock.png");
//            break;
//        case 1:
//            type = ObstacleType::TREE;
//            texture = &rm.GetTexture("tree.png");
//            break;
//        case 2:
//            type = ObstacleType::FOUNTAIN;
//            texture = &rm.GetTexture("fountain_sheet.png"); // Texture avec les 4 frames
//            break;
//        case 3:
//            type = ObstacleType::FLOWER;
//            texture = &rm.GetTexture("flower.png");
//            break;
//        case 4:
//            type = ObstacleType::GRASS;
//            texture = &rm.GetTexture("grass.png");
//            break;
//        }
//
//        // Création et ajout
//        if (texture) {
//            m_obstacles.push_back(Obstacle(type, *texture, { x, y }));
//        }
//    }
//}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "Arene 2D");
    sf::View camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(1900.f, 800.f));
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Clock clock;
    TileMap map;
    Player player;

    ResourceManager resourceManager;
    CollisionManager collisionMgr;
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
    obstacleManager.Initialize(40, worldBounds, resourceManager);
    collisionMgr.addHurtbox(&player.hurtbox);
    collisionMgr.addHitbox(&player.hitbox);
    collisionMgr.addHitbox(&player.hitbox2);

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

        enemyManager.HandleWaves(worldBounds);

        collisionMgr.checkCollisions();
        collisionMgr.clear();
        player.Update(window, dt, worldBounds);
        enemyManager.Update(dt, player, worldBounds, obstacleManager.GetObstacles(), collisionMgr);
        collisionMgr.CheckMapCollisions(player.getSprite(), obstacleManager.GetObstacles());
        window.draw(oceanSprite);
        window.draw(map);
        obstacleManager.Draw(window);
        enemyManager.Draw(window);

        window.draw(player.getSprite());
		//test debug
//        collisionMgr.DebugDrawFeetBox(window, player.getSprite());
//        enemyManager.DebugDrawCollisions(window, collisionMgr);
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
*/