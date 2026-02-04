#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ChaseState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
using namespace NpcAi;

class Npc
{
private:
    int value = 100;

    FSM::StateMachine<NpcContext> fsm;
    sf::RectangleShape shape;
public:
    NpcContext context{};
    Npc() : shape({ 30.f, 30.f }) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({ 200.f, 200.f });
        context.npcShape = &shape;
    }
    sf::RectangleShape& getShape() { return shape; }
    void Init()
    {
        PatrolState* patrolState = fsm.CreateState<PatrolState>();
        ChaseState* chaseState = fsm.CreateState<ChaseState>();

        patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);

        chaseState->AddTransition([](const NpcContext _context)
        {
            return !Conditions::IsSeeingPlayer(_context);
        }, patrolState);

        fsm.Init(patrolState, context);
    }

    void Update()
    {
        fsm.Update(context);
    }
};
