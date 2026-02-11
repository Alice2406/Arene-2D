#include "ObstacleManager.h"
#include "../Animation-Assets/AssetPath.h"
#include <iostream>

void ObstacleManager::Initialize(int count, sf::Vector2f mapSize, ResourceManager& resources)
{
    m_texture = resources.GetTexture(AssetPaths::Environment::ROCK);

    int spawned = 0;
    int attempts = 0;

    float edgeMargin = 150.f;

    while (spawned < count && attempts < count * 10)
    {
        attempts++;

        int safeWidth = (int)(mapSize.x - (edgeMargin * 2));
        int safeHeight = (int)(mapSize.y - (edgeMargin * 2));

        if (safeWidth <= 0 || safeHeight <= 0) break;

        float x = edgeMargin + (rand() % safeWidth);
        float y = edgeMargin + (rand() % safeHeight);

        if (x < 300.f && y < 300.f) continue;

        m_obstacles.emplace_back(m_texture, sf::Vector2f(x, y));
        spawned++;
    }

    std::cout << spawned << " obstacles generes avec marge de securite." << std::endl;
}

void ObstacleManager::Draw(sf::RenderWindow& window)
{
    for (auto& obs : m_obstacles)
    {
        obs.Draw(window);
    }
}