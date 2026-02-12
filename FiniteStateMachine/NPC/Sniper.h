#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../Core/HealthComponent.h"
#include "../Core/CollisionManager.h"
#include "../Core/CollisionBox.h"
#include "../NpcStates/ShootState.h"
#include "../NpcStates/FleeState.h"
#include "../NpcStates/AimState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
#include "SniperDataBase.h"
#include "../Animation-Assets/ResourceManager.h"

using namespace NpcAi;


class Sniper : public IDamageable
{
private:
    HealthComponent health;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    SniperData m_data;
    float m_flashTimer = 0.0f;
    const float FLASH_DURATION = 0.15f;
    FSM::StateMachine<NpcContext> fsm;
    sf::Texture* m_ptrProjectileTexture = nullptr;

public:
    CollisionBox hurtbox;
    NpcContext context{};
    explicit Sniper(SniperSkin skinType, sf::Texture& texture);
    void Init();
    void setPosition(const sf::Vector2f& position);
    sf::Sprite& getSprite();
    void Update(float dt);
    sf::FloatRect GetGlobalBounds() const;
    bool IsHit() const;
    void Draw(sf::RenderWindow& window);
    void handleDamage(float amount) override;
    bool IsDead() const;
    sf::Vector2f getPosition() const;
    void SetProjectileTexture(sf::Texture& tex);
};
