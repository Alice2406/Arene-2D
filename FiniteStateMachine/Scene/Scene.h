#pragma once
#include <SFML/Graphics.hpp>

enum class SceneType {
    None, 
    Menu,
    Game
};

class Scene
{
public:
    virtual ~Scene() = default;

    virtual SceneType Update(float dt, sf::RenderWindow& window) = 0;

    virtual void Draw(sf::RenderWindow& window) = 0;
};