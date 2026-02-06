#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ChaseState.h"
#include "../NpcStates/AttackState.h"
#include "../NpcStates/GuardState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
using namespace NpcAi;

class Tank
{
private:
    int value = 100;

    FSM::StateMachine<NpcContext> fsm;
    sf::RectangleShape shape;
public:
    NpcContext context{};
    Tank() : shape({ 30.f, 30.f }) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({ -10.f, -10.f });
        context.npcShape = &shape;
    }
    sf::RectangleShape& getShape() { return shape; }
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
    sf::Vector2f getPosition() { return shape.getPosition(); }
    void Update()
    {
        fsm.Update(context);
    }
};
