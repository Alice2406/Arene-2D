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

//test debug collision box player
void CollisionManager::DebugDrawFeetBox(sf::RenderWindow& window, const sf::Sprite& entitySprite)
{
    sf::FloatRect globalBounds = entitySprite.getGlobalBounds();

    float boxWidth = 30.f;
    float boxHeight = 15.f;
    float verticalOffset = 68.f; 

    float feetCenterX = globalBounds.position.x + globalBounds.size.x / 2.f;
    float feetCenterY = (globalBounds.position.y + globalBounds.size.y) - verticalOffset;

    sf::FloatRect feetBox(
        { feetCenterX - (boxWidth / 2.f),
        feetCenterY - boxHeight },
        { boxWidth,
        boxHeight }
    );

    // Dessin
    sf::RectangleShape debugShape;
    debugShape.setSize({ feetBox.size.x, feetBox.size.y });
    debugShape.setPosition(feetBox.position);
    debugShape.setFillColor(sf::Color::Transparent);
    debugShape.setOutlineColor(sf::Color::Magenta);
    debugShape.setOutlineThickness(2.f);
    window.draw(debugShape);
}

void CollisionManager::CheckMapCollisions(sf::Sprite& entitySprite, const std::vector<Obstacle>& obstacles)
{
    sf::FloatRect globalBounds = entitySprite.getGlobalBounds();

    float boxWidth = 30.f;
    float boxHeight = 15.f;

    float verticalOffset = 68.f;

    float feetCenterX = globalBounds.position.x + globalBounds.size.x / 2.f;

    float feetCenterY = (globalBounds.position.y + globalBounds.size.y) - verticalOffset;

    sf::FloatRect feetBox(
        { feetCenterX - (boxWidth / 2.f),
        feetCenterY - boxHeight },
        { boxWidth,
        boxHeight }
    );


    for (const auto& obs : obstacles)
    {
        if (!obs.IsSolid()) continue;

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
                float moveX = (dx > 0) ? -intersectX : intersectX;
                entitySprite.move({ moveX, 0.f });
            }
            else
            {
                float moveY = (dy > 0) ? -intersectY : intersectY;
                entitySprite.move({ 0.f, moveY });
            }
            globalBounds = entitySprite.getGlobalBounds();
            feetCenterX = globalBounds.position.x + globalBounds.size.x / 2.f;
            feetCenterY = globalBounds.position.y + globalBounds.size.y;

            feetBox.position = { feetCenterX - (boxWidth / 2.f), feetCenterY - boxHeight };
        }
    }
}