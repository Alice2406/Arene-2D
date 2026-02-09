#include "CollisionManager.h"
#include "../PlayerStates/Player.h"
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
            if (attack == target || !target->isActive) continue;

            if (attack->owner == target->owner) continue;

            if (attack->bounds.findIntersection(target->bounds)) {
                std::cout << "COLLISION DETECTEE !" << std::endl;

                Player* victim = static_cast<Player*>(target->owner);

                if (victim) {
                    victim->takeDamage(10);
                }
            }
        }
    }
}
