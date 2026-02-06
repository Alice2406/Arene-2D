#pragma once
#include "../Animation-Assets/Animator.h"

class NpcContext
{
public:
    sf::Sprite* npcSprite; 
    Animator* animator;
    float deltaTime;
    sf::Vector2f playerPos;
    float speed = 100.f; 
    float currentTimer = 0.0f;
    bool triggerGuard = false;
    bool isInvulnerable = false;
};
