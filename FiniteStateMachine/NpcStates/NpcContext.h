#pragma once
#include "../Animation-Assets/Animator.h"
#include "../NPC/EnemyProjectile.h"
#include "SFML/Graphics.hpp"

class NpcContext
{
public:
    sf::Sprite* npcSprite; 
    Animator* animator;
    float deltaTime;
    sf::Vector2f playerPos;
    sf::Vector2f baseScale = { 1.f, 1.f };
    float speed = 100.f; 
    float currentTimer = 0.0f;
    bool triggerGuard = false;
    bool isInvulnerable = false;
    std::vector<EnemyProjectile*>* projectileList = nullptr;
    sf::Texture* weaponTexture = nullptr;
    AnimConfig weaponConfig;
};
