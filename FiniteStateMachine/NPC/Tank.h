#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../Core/HealthComponent.h"
#include "../Core/CollisionManager.h"
#include "../Core/CollisionBox.h"
#include "../NpcStates/ChaseState.h"
#include "../NpcStates/AttackState.h"
#include "../NpcStates/GuardState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
#include "../Animation-Assets/Animator.h"
#include "../Animation-Assets/AssetPath.h"
#include "../Animation-Assets/ResourceManager.h"
#include "TankDataBase.h"
#include <iostream>

using namespace NpcAi;


class Tank : public IDamageable
{
private:
    HealthComponent health;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    TankData m_data;
    FSM::StateMachine<NpcContext> fsm;
    float m_flashTimer = 0.0f;
    const float FLASH_DURATION = 0.15f;

public:
    CollisionBox hurtbox;
    NpcContext context{};
    explicit Tank(TankSkin skinType, sf::Texture& texture);
    void Init();
    void handleDamage(float amount) override;
    bool IsDead() const override;
    bool IsHit() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::Sprite& getSprite();
    void Update(float dt);
    sf::FloatRect GetGlobalBounds() const;
    void Draw(sf::RenderWindow& window);
};
