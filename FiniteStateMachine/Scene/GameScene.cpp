#include "GameScene.h"
#include "../Animation-Assets/AssetPath.h"
#include <algorithm>

GameScene::GameScene(sf::RenderWindow& window, ResourceManager& rm)
    : m_resourceManager(rm),
    m_oceanSprite(rm.GetTexture("Water"))
{
    m_camera.setSize({ 1900.f, 800.f });
    m_camera.setCenter({ 0.f, 0.f });

    m_resourceManager.LoadAllGameTextures();

    if (!m_map.load(AssetPaths::Environment::LEVEL_1_DATA, AssetPaths::Environment::TILESET_GROUND, { 63, 63 })) {
        std::cout << "Erreur Asset" << std::endl;
    }

    m_oceanSprite.setTexture(m_resourceManager.GetTexture("Water"));
    m_oceanSprite.setTextureRect(sf::IntRect({ 0, 0 }, { 10000, 10000 }));
    m_oceanSprite.setPosition({ -5000.f, -5000.f });

    sf::Vector2u mapSizeInTiles = { 35, 20 };
    sf::Vector2u tileSize = { 63, 63 };
    m_worldBounds = {
        static_cast<float>(mapSizeInTiles.x * tileSize.x),
        static_cast<float>(mapSizeInTiles.y * tileSize.y)
    };

    m_obstacleManager.Initialize(40, m_worldBounds, m_resourceManager);

    m_collisionManager.addHurtbox(&m_player.hurtbox);
    m_collisionManager.addHitbox(&m_player.hitbox);
    m_collisionManager.addHitbox(&m_player.hitbox2);
}

SceneType GameScene::Update(float dt, sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        return SceneType::Menu;

    m_camera.setCenter(m_player.getPosition());

    m_enemyManager.HandleWaves(m_worldBounds);
    m_player.Update(window, dt, m_worldBounds);
    m_obstacleManager.Update(dt);

    m_enemyManager.Update(dt, m_player, m_worldBounds, m_obstacleManager.GetObstacles(), m_collisionManager);

    m_collisionManager.CheckMapCollisions(m_player.getSprite(), m_obstacleManager.GetObstacles());
    m_collisionManager.checkCollisions();
    m_collisionManager.clear();

    return SceneType::None;
}

void GameScene::Draw(sf::RenderWindow& window)
{
    window.setView(m_camera);

    window.draw(m_oceanSprite);
    window.draw(m_map);

    std::vector<RenderObject> drawQueue;

    sf::Sprite& pSprite = m_player.getSprite();
    drawQueue.push_back({ &pSprite, pSprite.getPosition().y + pSprite.getGlobalBounds().size.y });

    for (const auto& obs : m_obstacleManager.GetObstacles()) {
        const sf::Sprite& s = obs.GetSprite();
        drawQueue.push_back({ &s, s.getPosition().y + s.getGlobalBounds().size.y });
    }

    std::sort(drawQueue.begin(), drawQueue.end(), [](const RenderObject& a, const RenderObject& b) {
        return a.yDepth < b.yDepth;
        });

    for (const auto& obj : drawQueue) {
        window.draw(*obj.sprite);
    }

    m_enemyManager.Draw(window);


    //m_player.hurtbox.debugDraw(window);
    //m_player.hitbox.debugDraw(window);
    //m_player.hitbox2.debugDraw(window);
    //m_obstacleManager.DebugDraw(window);
}