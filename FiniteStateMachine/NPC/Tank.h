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
        GuardState* guardState = fsm.CreateState<GuardState>();
        AttackState* attackState = fsm.CreateState<AttackState>();
        patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
        chaseState->AddTransition(Conditions::IsInAttackRange, attackState);

        chaseState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsSeeingPlayer(_context);
            }, patrolState);
        attackState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsInAttackRange(_context);
            }, chaseState);
        fsm.Init(patrolState, context);
    }
    sf::Vector2f getPosition() { return shape.getPosition(); }
    void Update()
    {
        fsm.Update(context);
    }
};
