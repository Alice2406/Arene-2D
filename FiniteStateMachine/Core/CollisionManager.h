#pragma once
#include <vector>

class CollisionBox;

class IDamageable {
public:
    virtual void handleDamage(float amount) = 0;
    virtual bool IsDead() const = 0;
    virtual ~IDamageable() = default;
};

class CollisionManager {
private:
    std::vector<CollisionBox*> hitboxes;
    std::vector<CollisionBox*> hurtboxes;

public:
    void addHitbox(CollisionBox* _box);
    void addHurtbox(CollisionBox* _box);
    void checkCollisions();
    void clear();
};