#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
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


class Tank
{
private:
    int value = 100;
    int m_currentHealth;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    TankData m_data;
    FSM::StateMachine<NpcContext> fsm;
    float m_flashTimer = 0.0f;
    const float FLASH_DURATION = 0.15f;
public:
    NpcContext context{};
    Tank(TankSkin skinType, sf::Texture& texture) : m_sprite(m_texture), m_animator(m_sprite)
    {
        m_data = TankDatabase::GetData(skinType);
        m_sprite.setTexture(texture);
        context.npcSprite = &m_sprite;
        context.animator = &m_animator;
        context.speed = m_data.moveSpeed;

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
        m_currentHealth = m_data.health;
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
        attackState->AddTransition([](NpcContext& ctx)
            {
                return !Conditions::IsInAttackRange(ctx);
            }, chaseState);

        fsm.Init(patrolState, context);
    }

    void TakeDamage(int damageAmount)
    {
        m_currentHealth -= damageAmount;

        m_sprite.setColor(sf::Color(255, 100, 100));
        m_flashTimer = FLASH_DURATION;

    }

    bool IsDead() const
    {
        return m_currentHealth <= 0;
    }
    void setPosition(const sf::Vector2f& position)
    {
        m_sprite.setPosition(position);
    }

    sf::Sprite& getSprite() { return m_sprite; }

    void Update(float dt)
    {
        fsm.Update(context);
        m_animator.Update(dt);
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

    bool IsHit() const {
        return m_flashTimer > 0.0f;
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
};
