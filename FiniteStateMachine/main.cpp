#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <optional> 
#include "Animation-Assets/AssetPath.h"
#include "NPC/EnemyManager.h" 
#include "PlayerStates/Player.h"
#include "Core/CollisionManager.h"
#include "Obstacles/ObstacleManager.h"
#include "Animation-Assets/ResourceManager.h"
#include "TileMap.h"
#include "HealthBar.h"

struct RenderObject {
    const sf::Sprite* sprite;
    float yDepth;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "Arene 2D");
    sf::View camera(sf::Vector2f(0.f, 0.f), sf::Vector2f(1900.f, 800.f));
    sf::View uiView(sf::Vector2f(950.f, 400.f), sf::Vector2f(1900.f, 800.f));
    window.setFramerateLimit(60);
    srand(static_cast<unsigned int>(time(NULL)));

    sf::Clock clock;

    ResourceManager resourceManager;

    resourceManager.LoadAllGameTextures();

    TileMap map;

    if (!map.load(AssetPaths::Environment::LEVEL_1_DATA, AssetPaths::Environment::TILESET_GROUND, { 63, 63 }))
    {
        return -1;
    }

    sf::Sprite oceanSprite(resourceManager.GetTexture("Water"));
    oceanSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));
    oceanSprite.setPosition({ -5000.f, -5000.f });

    sf::Vector2u mapSizeInTiles = { 35, 20 };
    sf::Vector2u tileSize = { 63, 63 };
    sf::Vector2f worldBounds = {
        static_cast<float>(mapSizeInTiles.x * tileSize.x),
        static_cast<float>(mapSizeInTiles.y * tileSize.y)
    };

    ObstacleManager obstacleManager;
    obstacleManager.Initialize(40, worldBounds, resourceManager);

    Player player;

    HealthBar healthBar({ 400.f, 40.f });
    healthBar.SetPosition({ (1900.f - 400.f) / 2.f, 800.f - 70.f });

    CollisionManager collisionMgr;
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

        enemyManager.HandleWaves(worldBounds);

        player.Update(window, dt, worldBounds);

        healthBar.Update(player.getHp(), player.getHealth().getMaxHealth());

        obstacleManager.Update(dt);

        enemyManager.Update(dt, player, worldBounds, obstacleManager.GetObstacles(), collisionMgr);

        collisionMgr.CheckMapCollisions(player.getSprite(), obstacleManager.GetObstacles());

        collisionMgr.checkCollisions();
        collisionMgr.clear();

        window.clear();
        window.setView(camera);

        window.draw(oceanSprite);
        window.draw(map);

        std::vector<RenderObject> drawQueue;

        sf::Sprite& pSprite = player.getSprite();
        drawQueue.push_back({ &pSprite, pSprite.getPosition().y + pSprite.getGlobalBounds().size.y });

        for (const auto& obs : obstacleManager.GetObstacles())
        {
            const sf::Sprite& s = obs.GetSprite();
            drawQueue.push_back({ &s, s.getPosition().y + s.getGlobalBounds().size.y });
        }

        std::sort(drawQueue.begin(), drawQueue.end(), [](const RenderObject& a, const RenderObject& b) {
            return a.yDepth < b.yDepth;
            });

        for (const auto& obj : drawQueue)
        {
            window.draw(*obj.sprite);
        }
        enemyManager.Draw(window);

        player.hurtbox.debugDraw(window);
        player.hitbox.debugDraw(window);
        player.hitbox2.debugDraw(window);

        window.setView(uiView);
        healthBar.Draw(window);

        window.display();
    }

    return 0;
}