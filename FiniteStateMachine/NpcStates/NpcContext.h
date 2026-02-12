#pragma once
#include "../Animation-Assets/Animator.h"
#include "../Animation-Assets/SharedData.h"
#include "../NPC/EnemyProjectile.h"
#include "../NPC/SniperData.h"
#include "SFML/Graphics.hpp"

class EnemyProjectile;
struct SniperData;
class Berserker;
class Tank;
class Sniper;

class EnemyProjectile;

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
    sf::Vector2f worldBounds;
    void* ownerSniper = nullptr;
    const SniperData* sniperData = nullptr;

    Berserker* berserker = nullptr;
    Tank* tank = nullptr;
    Sniper* sniper = nullptr;
};
