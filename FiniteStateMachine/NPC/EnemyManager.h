#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

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

public:
    ~EnemyManager();

    void SpawnTank(TankSkin skin, sf::Vector2f position);
    void SpawnBerserker(BerserkerSkin skin, sf::Vector2f position);
    void SpawnSniper(SniperSkin skin, sf::Vector2f position);
    void Update(float dt, Player& player);

    void Draw(sf::RenderWindow& window);
};