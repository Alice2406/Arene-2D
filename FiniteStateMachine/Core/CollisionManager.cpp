#include "CollisionManager.h"
#include "CollisionBox.h"
#include <iostream>

void CollisionManager::addHurtbox(CollisionBox* _box)
{
    hurtboxes.push_back(_box);
}

void CollisionManager::addHitbox(CollisionBox* _box)
{
    hitboxes.push_back(_box);
}

void CollisionManager::checkCollisions()
{
    for (auto* attack : hitboxes) {
        if (!attack->isActive) continue;

        for (auto* target : hurtboxes) {
            if (!target->isActive) continue;
            if (attack->owner == target->owner) continue;

            if (attack->bounds.findIntersection(target->bounds)) {
                std::cout << "COLLISION DETECTEE !" << std::endl;

                IDamageable* victim = static_cast<IDamageable*>(target->owner);

                if (victim && !victim->IsDead()) {
                    victim->handleDamage(10.0f);
                }
            }
        }
    }
}

void CollisionManager::clear()
{
    hitboxes.clear();
    hurtboxes.clear();
}