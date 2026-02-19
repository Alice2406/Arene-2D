#include "GameScene.h"
#include "../Animation-Assets/AssetPath.h"
#include <algorithm>

GameScene::GameScene(sf::RenderWindow& window, ResourceManager& rm)
    : m_resourceManager(rm), m_font(), m_gameOverTitle(m_font), m_finalScoreText(m_font), m_textQuit(m_font),
    m_oceanSprite(rm.GetTexture("Water")), m_scoreText(m_font), m_btnQuit(rm.GetTexture("BtnQuit"))
{
    if (!m_font.openFromFile(AssetPaths::UI::MAIN_FONT)) {
        std::cerr << "ERREUR CRITIQUE : Impossible de charger la police !" << std::endl;
    }
    m_camera.setSize({ 1900.f, 800.f });
    m_camera.setCenter({ 0.f, 0.f });
    m_score = 0;
    m_isGameOver = false;
    m_resourceManager.LoadAllGameTextures();
    InitGameOverUI(window.getSize());

    if (!m_map.load(AssetPaths::Environment::LEVEL_1_DATA, AssetPaths::Environment::TILESET_GROUND, { 63, 63 })) {
        std::cout << "Erreur Asset" << std::endl;
    }
    m_score = 0;

    m_scoreText.setFont(m_font);
    m_scoreText.setString("Score: 0");
    m_scoreText.setCharacterSize(30);
    m_scoreText.setFillColor(sf::Color::Yellow); 
    m_scoreText.setPosition({ 10.f, 10.f });
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
    healthBar.SetPosition({ (1900.f - 400.f) / 2.f, 800.f - 70.f });
    m_collisionManager.addHurtbox(&m_player.hurtbox);
    m_collisionManager.addHitbox(&m_player.hitbox);
    m_collisionManager.addHitbox(&m_player.hitbox2);
}

void GameScene::InitGameOverUI(sf::Vector2u windowSize)
{
    float winW = static_cast<float>(windowSize.x);
    float winH = static_cast<float>(windowSize.y);
    float cx = winW / 2.f;
    float cy = winH / 2.f;

    m_darkOverlay.setSize({ winW, winH });
    m_darkOverlay.setFillColor(sf::Color(0, 0, 0, 200));

    m_gameOverTitle.setFont(m_font);
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setCharacterSize(100);
    m_gameOverTitle.setFillColor(sf::Color::Red);
    m_gameOverTitle.setOutlineColor(sf::Color::Black);
    m_gameOverTitle.setOutlineThickness(5);

    sf::FloatRect titleB = m_gameOverTitle.getLocalBounds();
    m_gameOverTitle.setOrigin({ titleB.size.x / 2.f, titleB.size.y / 2.f });
    m_gameOverTitle.setPosition({ cx, cy - 150.f });

    m_finalScoreText.setFont(m_font);
    m_finalScoreText.setCharacterSize(50);
    m_finalScoreText.setFillColor(sf::Color::Yellow);
    m_finalScoreText.setOutlineColor(sf::Color::Black);
    m_finalScoreText.setOutlineThickness(3);
    m_finalScoreText.setPosition({ cx, cy });

    m_btnQuit.setTexture(m_resourceManager.GetTexture("BtnQuit"));
    m_btnQuit.setScale({ 1.5f, 1.5f });

    sf::FloatRect btnB = m_btnQuit.getLocalBounds();
    m_btnQuit.setOrigin({ btnB.size.x / 2.f, btnB.size.y / 2.f });
    m_btnQuit.setPosition({ cx, cy + 150.f });

    m_textQuit.setFont(m_font);
    m_textQuit.setString("Quitter");
    m_textQuit.setCharacterSize(60);
    m_textQuit.setFillColor(sf::Color(50, 50, 50));

    sf::FloatRect txtB = m_textQuit.getLocalBounds();
    m_textQuit.setOrigin({ txtB.size.x / 2.f, txtB.size.y / 2.f });
    m_textQuit.setPosition({ cx, cy + 125.f });
}

SceneType GameScene::Update(float dt, sf::RenderWindow& window)
{
    if (m_isGameOver)
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel, window.getDefaultView());

        if (m_btnQuit.getGlobalBounds().contains(mousePos))
        {
            m_btnQuit.setColor(sf::Color(200, 200, 200));
            m_textQuit.setFillColor(sf::Color::Black);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                window.close();
            }
        }
        else
        {
            m_btnQuit.setColor(sf::Color::White);
            m_textQuit.setFillColor(sf::Color(50, 50, 50));
        }

        return SceneType::None;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        return SceneType::Menu;

    m_camera.setCenter(m_player.getPosition());

    m_enemyManager.HandleWaves(m_worldBounds);
    m_player.Update(window, dt, m_worldBounds);
    healthBar.Update(m_player.getHp(), m_player.getHealth().getMaxHealth());
    m_obstacleManager.Update(dt);

    int pointsRecuperes = m_enemyManager.Update(dt, m_player, m_worldBounds, m_obstacleManager.GetObstacles(), m_collisionManager);
    if (pointsRecuperes > 0)
    {
        m_score += pointsRecuperes;

        m_scoreText.setString("Score: " + std::to_string(m_score));
    }

    m_collisionManager.CheckMapCollisions(m_player.getSprite(), m_obstacleManager.GetObstacles());
    m_collisionManager.checkCollisions();
    m_collisionManager.clear();
    if (m_player.getHp() <= 0)
    {
        m_isGameOver = true;

        m_finalScoreText.setString("Score Final : " + std::to_string(m_score));

        sf::FloatRect b = m_finalScoreText.getLocalBounds();
        m_finalScoreText.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });

        sf::Vector2u winSize = window.getSize();
        m_finalScoreText.setPosition({ winSize.x / 2.f, winSize.y / 2.f });
    }
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
    window.setView(window.getDefaultView());
    healthBar.Draw(window);
    if (!m_isGameOver) {
        window.draw(m_scoreText);
    }

    if (m_isGameOver)
    {
        window.draw(m_darkOverlay);    
        window.draw(m_gameOverTitle);
        window.draw(m_finalScoreText);

        window.draw(m_btnQuit);        
        window.draw(m_textQuit);       
    }
}