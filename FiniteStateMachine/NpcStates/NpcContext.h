#pragma once

class Npc;

class NpcContext
{
public:
    sf::Shape* npcShape;
    Npc* npc;
    sf::Vector2f playerPos;
    float speed = 100.f; 
    float deltaTime;
    float currentTimer = 0.0f;
    bool triggerGuard = false;
    bool isInvulnerable = false;
};
