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
#include <iostream>
using namespace NpcAi;

enum class TankSkin {
    MINOTAUR,
    PANDA,
    SKULL,
    TURTLE
};

class Tank
{
private:
    int value = 100;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    FSM::StateMachine<NpcContext> fsm;
public:
    NpcContext context{};
    Tank(TankSkin skinType) : m_sprite(m_texture), m_animator(m_sprite)
    {
        context.npcSprite = &m_sprite;
        context.animator = &m_animator;
        std::string pathIdle = "";
        std::string pathWalk = "";
        std::string pathGuard = "";
        std::string pathAttack = "";

        int framesWalk = 7;
        int framesAttack = 10;
        float speedWalk = 0.1f;
        switch (skinType)
        {
        case TankSkin::TURTLE:
            pathIdle = AssetPaths::Tank::Turtle::IDLE;
            pathWalk = AssetPaths::Tank::Turtle::WALK;
            pathGuard = AssetPaths::Tank::Turtle::GUARD;
            pathAttack = AssetPaths::Tank::Turtle::ATTACK;
            framesWalk = 7;
            framesAttack = 10;
            m_sprite.setScale({ 0.7f , 0.7f});
            break;
        }

        if (pathIdle.empty()) return;

        sf::Texture& tIdle = m_resources.GetTexture(pathIdle);
        sf::Texture& tWalk = m_resources.GetTexture(pathWalk);
        sf::Texture& tGuard = m_resources.GetTexture(pathGuard);
        sf::Texture& tAttack = m_resources.GetTexture(pathAttack);

        m_animator.AddAnimation("Idle", tIdle, { 320,320 }, 10, 0.5f, true);
        m_animator.AddAnimation("Walk", tWalk, { 320,320 }, framesWalk, speedWalk);
        m_animator.AddAnimation("Guard", tGuard, { 320,320 }, 6, 1.0f);
        m_animator.AddAnimation("Attack", tAttack, { 320,320 }, framesAttack, 0.1f, true);

        m_animator.SwitchAnimation("Idle");
        m_sprite.setOrigin({ 160, 160 });
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
    void setPosition(const sf::Vector2f& position)
    {
        m_sprite.setPosition(position);
    }
    sf::Sprite& getSprite() { return m_sprite; }
    void Update(float dt)
    {
        fsm.Update(context);
        m_animator.Update(dt);
    }
    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }
};
