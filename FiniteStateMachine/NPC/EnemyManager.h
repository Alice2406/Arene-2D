#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../NPC/EnemyProjectile.h"
#include "../Core/CollisionManager.h"
#include "Tank.h"
#include "Berserker.h"
#include "Sniper.h"

class Player;
class EnemyManager
{
private:
    std::vector<Tank*> m_tanks;
    std::vector<Berserker*> m_berserkers;
    std::vector<Sniper*> m_snipers;
    std::vector<EnemyProjectile*> m_projectiles;
    ResourceManager m_resources;
    int m_waveNumber = 0;
public:
    ~EnemyManager();
    template <typename T>
    void keepInsideMap(T& enemy, sf::Vector2f worldBounds);
    void HandleWaves(sf::Vector2f mapSize);
    //test debug collision box ennemy
    void DebugDrawCollisions(sf::RenderWindow& window, CollisionManager& colManager);
    void SpawnTank(TankSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    void SpawnBerserker(BerserkerSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    void SpawnSniper(SniperSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    int Update(float dt, Player& player, sf::Vector2f worldBounds, const std::vector<Obstacle>& obstacles, CollisionManager& collisionMgr);
    void Draw(sf::RenderWindow& window);
};

#include "EnemyManager.inl"