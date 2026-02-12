#pragma once
#include "SFML/Graphics.hpp"

class CollisionBox
{
private:
    sf::RectangleShape debugShape;

public:
    sf::FloatRect bounds;
    sf::Vector2f offset;
    bool isActive = true;
    void* owner = nullptr;

    bool isProjectile = false;
    void* projectileOwner = nullptr;
    bool isPlayer = false;

    CollisionBox(sf::Vector2f size = { 0, 0 }, sf::Vector2f _offset = { 0, 0 });
    void Update(sf::Vector2f ownerPos, float scaleX);
    void debugDraw(sf::RenderWindow& window);
};

