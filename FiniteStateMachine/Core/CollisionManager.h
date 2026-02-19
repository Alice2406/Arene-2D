#pragma once
#include <vector>
#include "../Obstacles/Obstacle.h"
class CollisionBox;

class IDamageable {
public:
    virtual void handleDamage(float amount) = 0;
    virtual bool IsDead() const = 0;
    virtual ~IDamageable() = default;
};

class IDestructible {
public:
    virtual void Destroy() = 0;
    virtual ~IDestructible() = default;
};

class CollisionManager {
private:
    std::vector<CollisionBox*> hitboxes;
    std::vector<CollisionBox*> hurtboxes;

public:
    void DebugDrawFeetBox(sf::RenderWindow& window, const sf::Sprite& entitySprite);

    void CheckMapCollisions(sf::Sprite& entitySprite, const std::vector<Obstacle>& obstacles);
    void addHitbox(CollisionBox* _box);
    void addHurtbox(CollisionBox* _box);
    void checkCollisions();
    void clear();
};