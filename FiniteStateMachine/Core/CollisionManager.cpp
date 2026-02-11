#include "CollisionManager.h"
#include "CollisionBox.h"
#include <cmath>
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

void CollisionManager::CheckMapCollisions(sf::Sprite& entitySprite, const std::vector<Obstacle>& obstacles)
{
    sf::FloatRect entityBounds = entitySprite.getGlobalBounds();
    float entityHeight = entityBounds.size.y * 0.3f;

    sf::FloatRect feetBox(
        { entityBounds.position.x + 10.f, entityBounds.position.y + entityBounds.size.y - entityHeight }, 
        { entityBounds.size.x - 20.f, entityHeight }
    );

    for (const auto& obs : obstacles)
    {
        sf::FloatRect obsBox = obs.GetHitbox(); 

        if (feetBox.findIntersection(obsBox))
        {

            sf::Vector2f feetCenter = { feetBox.position.x + feetBox.size.x / 2.f, feetBox.position.y + feetBox.size.y / 2.f };
            sf::Vector2f obsCenter = { obsBox.position.x + obsBox.size.x / 2.f, obsBox.position.y + obsBox.size.y / 2.f };

            float dx = feetCenter.x - obsCenter.x;
            float dy = feetCenter.y - obsCenter.y;

            float intersectX = std::abs(dx) - (feetBox.size.x / 2.f + obsBox.size.x / 2.f);
            float intersectY = std::abs(dy) - (feetBox.size.y / 2.f + obsBox.size.y / 2.f);

            if (intersectX > intersectY) 
            {
                if (dx > 0) entitySprite.move({ -intersectX, 0.f }); 
                else        entitySprite.move({ intersectX, 0.f });  
            }
            else
            {
                if (dy > 0) entitySprite.move({ 0.f, -intersectY }); 
                else        entitySprite.move({ 0.f, intersectY });  
            }
            entityBounds = entitySprite.getGlobalBounds();
            feetBox.position = { entityBounds.position.x + 10.f, entityBounds.position.y + entityBounds.size.y - entityHeight };
        }
    }
}