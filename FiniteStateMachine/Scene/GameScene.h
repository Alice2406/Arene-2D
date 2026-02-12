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

    TileMap m_map;
    Player m_player;
    sf::Sprite m_oceanSprite;

    sf::Vector2f m_worldBounds;

public:
    GameScene(sf::RenderWindow& window, ResourceManager& rm);

    virtual SceneType Update(float dt, sf::RenderWindow& window) override;
    virtual void Draw(sf::RenderWindow& window) override;
};