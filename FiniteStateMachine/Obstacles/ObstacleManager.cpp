#include "ObstacleManager.h"
#include <iostream>

void ObstacleManager::Initialize(int count, sf::Vector2f mapSize, ResourceManager& resources)
{
    m_obstacles.clear(); 

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

        int randomPick = rand() % 10;

        ObstacleType type;
        std::string textureKey; 

        switch (randomPick)
        {
        case 0: type = ObstacleType::ROCK1; textureKey = "Rock1"; break;
        case 1: type = ObstacleType::ROCK2; textureKey = "Rock2"; break;
        case 2: type = ObstacleType::ROCK3; textureKey = "Rock3"; break;
        case 3: type = ObstacleType::ROCK4; textureKey = "Rock4"; break;

        case 4: type = ObstacleType::TREE;  textureKey = "Tree"; break;

        case 5: type = ObstacleType::SHEEP1; textureKey = "Sheep1"; break;
        case 6: type = ObstacleType::SHEEP2; textureKey = "Sheep2"; break;

        case 7: type = ObstacleType::BUSHE1; textureKey = "Bush1"; break;
        case 8: type = ObstacleType::BUSHE2; textureKey = "Bush2"; break;
        case 9: type = ObstacleType::BUSHE3; textureKey = "Bush3"; break;

        default: type = ObstacleType::ROCK1; textureKey = "Rock1"; break;
        }

        m_obstacles.emplace_back(type, resources.GetTexture(textureKey), sf::Vector2f(x, y));

        spawned++;
    }

    std::cout << spawned << " obstacles generes (Rochers, Moutons, Arbres...)." << std::endl;
}

void ObstacleManager::Update(float dt)
{
    for (auto& obs : m_obstacles)
    {
        obs.Update(dt);
    }
}

void ObstacleManager::Draw(sf::RenderWindow& window)
{
    for (auto& obs : m_obstacles)
    {
        obs.Draw(window);
    }
}