#pragma once
#include "SFML/Graphics.hpp"

class CollisionBox
{
public:
    sf::FloatRect bounds;
    sf::Vector2f offset;
    sf::RectangleShape debugShape;
    float rotation = 0.f;

    void* owner = nullptr;
    void* projectileOwner = nullptr;
    bool isActive = false;
    bool isPlayer = false;
    bool isProjectile = false;

    float damage = 10.0f;
    bool hasHit = false;

    CollisionBox() = default;
    CollisionBox(sf::Vector2f size, sf::Vector2f _offset);

    void Update(sf::Vector2f ownerPos, float scaleX, float rotationAngle = 0.f);
    void debugDraw(sf::RenderWindow& window);
    void ResetHit();
};