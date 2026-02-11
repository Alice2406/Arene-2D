#pragma once
#include <vector>
#include "Obstacle.h"
#include "../Animation-Assets/ResourceManager.h"

class ObstacleManager
{
private:
    std::vector<Obstacle> m_obstacles;
    sf::Texture m_texture;

public:
    void Initialize(int count, sf::Vector2f mapSize, ResourceManager& resources);
    void Draw(sf::RenderWindow& window);
    const std::vector<Obstacle>& GetObstacles() const { return m_obstacles; }
};