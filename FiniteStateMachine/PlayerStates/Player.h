#pragma once
#include "PlayerContext.h"
#include "../Core/CollisionManager.h"
#include "../Core/CollisionBox.h"
#include "../Core/HealthComponent.h"
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"

class Player : public IDamageable
{
private:
    sf::IntRect currentRect;
    int frameWidth, frameHeight, frameCount;
    int currentFrame = 0;
    float animationTimer = 0.0f;
    float animationSpeed;
    bool isLooping;

    HealthComponent health;
    float speed;
    bool isInvulnerable = false;
    float invulnTimer = 0.f;

public:
    sf::Texture textureIdle, textureRun, textureAttack, textureDeath;
    sf::Sprite sprite;

    CollisionBox hurtbox;
    CollisionBox hitbox;
    CollisionBox hitbox2;

    Player();

    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    int getCurrentFrame() const { return currentFrame; }
    int getFrameCount() const { return frameCount; }
    HealthComponent& getHealth() { return health; }
    float getHp() const { return health.getHealth(); }
    sf::Sprite& getSprite() { return sprite; }
    float getAttackDamage() const { return 25.0f; }

    void setAnimation(const sf::Texture& tex, int w, int h, int count, float speed, bool loop, int row);
    void Update(sf::RenderWindow& window, float _dt, sf::Vector2f worldBounds);
    void handleDamage(float damage) override;
    bool IsDead() const override { return health.IsDead(); }

    PlayerContext context;
    FSM::StateMachine<PlayerContext> fsm;
};