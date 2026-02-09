#pragma once
#include "PlayerContext.h"
#include "../Core/CollisionBox.h"
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"

class Player
{
private:
    // Animation
    sf::IntRect currentRect;
    int frameWidth, frameHeight, frameCount;
    int currentFrame = 0;
    float animationTimer = 0.0f;
    float animationSpeed;
    bool isLooping;

    // Statistiques & Gameplay
    float speed;
    int hp = 100;
    int maxHp = 100;
    bool isInvulnerable = false;
    float invulnTimer = 0.f;

public:
    // Assets
    sf::Texture textureIdle, textureRun, textureAttack, textureDeath;
    sf::Sprite sprite;

    // Physique
    CollisionBox hurtbox;
    CollisionBox hitbox;
    CollisionBox hitbox2;

    Player();

    // Getters / Setters
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    int getCurrentFrame() const { return currentFrame; }
    int getFrameCount() const { return frameCount; }
    int getHp() const { return hp; }
    sf::Sprite& getSprite() { return sprite; }

    // Méthodes principales
    void takeDamage(int damage);
    void setAnimation(const sf::Texture& tex, int w, int h, int count, float speed, bool loop, int row);
    void Update(sf::RenderWindow& window, float _dt);
    bool CheckHit(const sf::FloatRect& enemyBounds);

    PlayerContext context;
    FSM::StateMachine<PlayerContext> fsm;
};