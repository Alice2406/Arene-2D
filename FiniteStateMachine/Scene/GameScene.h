#pragma once
#include "Scene.h"
#include "../PlayerStates/Player.h"
#include "../NPC/EnemyManager.h"
#include "../Obstacles/ObstacleManager.h"
#include "../Core/CollisionManager.h"
#include "../Animation-Assets/ResourceManager.h"
#include "../TileMap.h"

struct RenderObject {
    const sf::Sprite* sprite;
    float yDepth;
};

class GameScene : public Scene
{
private:
    sf::View m_camera;

    ResourceManager& m_resourceManager;

    ObstacleManager m_obstacleManager;
    CollisionManager m_collisionManager;
    EnemyManager m_enemyManager;
    sf::Font m_font;
    TileMap m_map;
    Player m_player;
    sf::Sprite m_oceanSprite;
    int m_score;
    sf::Text m_scoreText;
    sf::Vector2f m_worldBounds;

    bool m_isGameOver;
    sf::RectangleShape m_darkOverlay;
    sf::Text m_gameOverTitle; 
    sf::Text m_finalScoreText;

    sf::Sprite m_btnQuit;       
    sf::Text   m_textQuit;

public:
    void InitGameOverUI(sf::Vector2u windowSize);
    GameScene(sf::RenderWindow& window, ResourceManager& rm);
    virtual SceneType Update(float dt, sf::RenderWindow& window) override;
    virtual void Draw(sf::RenderWindow& window) override;
};