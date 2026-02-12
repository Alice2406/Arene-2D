#pragma once
#include <vector>
#include "Obstacle.h"
#include "../Animation-Assets/ResourceManager.h"
#include <SFML/Graphics.hpp>


class ObstacleManager
{
private:
    std::vector<Obstacle> m_obstacles;

public:
    void Initialize(int count, sf::Vector2f mapSize, ResourceManager& resources);

    void Update(float dt);

    void Draw(sf::RenderWindow& window);

    const std::vector<Obstacle>& GetObstacles() const { return m_obstacles; }

    void DebugDraw(sf::RenderWindow& window);
};