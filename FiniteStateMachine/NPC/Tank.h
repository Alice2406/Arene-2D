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
    TankSkin m_skinType;
    CollisionBox hurtbox;
    CollisionBox hitbox;
    NpcContext context{};

    Tank(TankSkin skinType, sf::Texture& texture) : m_sprite(m_texture), m_animator(m_sprite), m_skinType(skinType)
    {
        m_data = TankDatabase::GetData(skinType);
        m_sprite.setTexture(texture);
        context.npcSprite = &m_sprite;
        context.animator = &m_animator;
        context.speed = m_data.moveSpeed;
        context.tank = this;

        sf::Texture& texIdle = m_resources.GetTexture(m_data.idle.texturePath);
        sf::Texture& texWalk = m_resources.GetTexture(m_data.walk.texturePath);
        sf::Texture& texAttack = m_resources.GetTexture(m_data.attack.texturePath);
        sf::Texture& texGuard = m_resources.GetTexture(m_data.guard.texturePath);

        m_animator.AddAnimation("Idle", texIdle, m_data.idle.frameSize, m_data.idle.frameCount, m_data.idle.speed);
        m_animator.AddAnimation("Walk", texWalk, m_data.walk.frameSize, m_data.walk.frameCount, m_data.walk.speed);
        m_animator.AddAnimation("Attack", texAttack, m_data.attack.frameSize, m_data.attack.frameCount, m_data.attack.speed);
        m_animator.AddAnimation("Guard", texGuard, m_data.guard.frameSize, m_data.guard.frameCount, m_data.guard.speed);
        m_sprite.setOrigin({ m_data.idle.frameSize.x / 2.f, m_data.idle.frameSize.y / 2.f });

        m_animator.SwitchAnimation("Idle");

        hurtbox = CollisionBox(m_data.hurtboxSize, m_data.hurtboxOffset);
        hurtbox.owner = this;
        hurtbox.isActive = true;
        hurtbox.isPlayer = false;

        hitbox = CollisionBox(m_data.hitboxSize, m_data.hitboxOffset);
        hitbox.owner = this;
        hitbox.isActive = false;

        health = HealthComponent(m_data.health);
    }
    void Init()
    {
        PatrolState* patrolState = fsm.CreateState<PatrolState>();
        ChaseState* chaseState = fsm.CreateState<ChaseState>();
        AttackState* attackState = fsm.CreateState<AttackState>();
        GuardState* guardState = fsm.CreateState<GuardState>();

        patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);

        chaseState->AddTransition([](NpcContext& ctx) {
            return !Conditions::IsSeeingPlayer(ctx);
            }, patrolState);

        patrolState->AddTransition([](NpcContext& ctx) {
            return ctx.triggerGuard;
            }, guardState);

        chaseState->AddTransition([](NpcContext& ctx) {
            return ctx.triggerGuard;
            }, guardState);

        guardState->AddTransition([](NpcContext& ctx) {
            return ctx.currentTimer >= 1.0f;
            }, chaseState);

        chaseState->AddTransition(Conditions::IsInAttackRange, attackState);
        attackState->AddTransition([attackState](NpcContext& ctx)
            {
                return attackState->IsFinished();
            }, chaseState);

        fsm.Init(patrolState, context);
    }

    void handleDamage(float amount) override
    {
        if (health.IsDead()) return;

        health.takeDamage(amount);

        m_sprite.setColor(sf::Color(255, 100, 100));
        m_flashTimer = FLASH_DURATION;

    }

    bool IsDead() const override
    {
        return health.IsDead();
    }

    bool IsHit() const {
        return m_flashTimer > 0.0f;
    }

    void setPosition(const sf::Vector2f& position)
    {
        m_sprite.setPosition(position);
    }

    sf::Vector2f getPosition() const
    {
        return m_sprite.getPosition();
    }

    sf::Sprite& getSprite()
    {
        return m_sprite;
    }

    void Update(float dt)
    {
        fsm.Update(context);
        m_animator.Update(dt);

        hurtbox.Update(m_sprite.getPosition(), m_sprite.getScale().x);
        hitbox.Update(m_sprite.getPosition(), m_sprite.getScale().x);

        if (m_flashTimer > 0)
        {
            m_flashTimer -= dt;
            if (m_flashTimer <= 0)
            {
                m_sprite.setColor(sf::Color::White);
            }
        }
    }

    sf::FloatRect GetGlobalBounds() const { return m_sprite.getGlobalBounds(); }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);

        hurtbox.debugDraw(window);
        hurtbox.debugDraw(window);
        hitbox.debugDraw(window);
    }
};