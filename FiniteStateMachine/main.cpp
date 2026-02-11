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
    CollisionManager collisionMgr;
    sf::Texture waterTexture;
    sf::Vector2u mapSizeInTiles = { 56, 28 };
    sf::Vector2u tileSize = { 63, 63 };

    sf::Vector2f worldBounds;
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
    collisionMgr.addHurtbox(&player.hurtbox);
    collisionMgr.addHitbox(&player.hitbox);
    collisionMgr.addHitbox(&player.hitbox2);

    EnemyManager enemyManager;

    enemyManager.SpawnTank(TankSkin::TURTLE, { -10.f, -10.f });
    enemyManager.SpawnTank(TankSkin::PANDA, { -10.f, -10.f });
    enemyManager.SpawnTank(TankSkin::MINOTAUR, { -10.f, -10.f });
    enemyManager.SpawnTank(TankSkin::SKULL, { -10.f, -10.f });

    enemyManager.SpawnBerserker(BerserkerSkin::BEAR, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::PADDLEFISH, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::LANCER, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::GNOME, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::TROLL, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::THIEF, { -10.f, -10.f });

    enemyManager.SpawnSniper(SniperSkin::GNOLL, { -10.f, -10.f });
    enemyManager.SpawnSniper(SniperSkin::HARPOONFISH, { -10.f, -10.f });
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
        collisionMgr.checkCollisions();
        collisionMgr.clear();
        player.Update(window, dt, worldBounds);
        enemyManager.Update(dt, player, worldBounds, collisionMgr);
        window.draw(oceanSprite);
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