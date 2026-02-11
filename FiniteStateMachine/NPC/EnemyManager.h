#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../NPC/EnemyProjectile.h"
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
    void keepInsideMap(T& enemy, sf::Vector2f worldBounds)
    {
        sf::Vector2f pos = enemy->getPosition();
        sf::FloatRect bounds = enemy->GetGlobalBounds();

        float originOffsetX = pos.x - bounds.position.x;
        float originOffsetY = pos.y - bounds.position.y;

        float width = bounds.size.x;
        float height = bounds.size.y;

        if (pos.x < originOffsetX)
            pos.x = originOffsetX;
        else if (pos.x > worldBounds.x - (width - originOffsetX))
            pos.x = worldBounds.x - (width - originOffsetX);

        if (pos.y < originOffsetY)
            pos.y = originOffsetY;
        else if (pos.y > worldBounds.y - (height - originOffsetY))
            pos.y = worldBounds.y - (height - originOffsetY);

        enemy->setPosition(pos);
    }
    void HandleWaves(sf::Vector2f mapSize);
    void SpawnTank(TankSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    void SpawnBerserker(BerserkerSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    void SpawnSniper(SniperSkin skin, sf::Vector2f position, sf::Vector2f mapSize);
    void Update(float dt, Player& player, sf::Vector2f worldBounds);

    void Draw(sf::RenderWindow& window);
};