#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ShootState.h"
#include "../NpcStates/FleeState.h"
#include "../NpcStates/AimState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
using namespace NpcAi;

enum class SniperSkin {
    GNOLL,
    HARPOON_FISH,
    SHAMAN
};
class Sniper
{
private:
    int value = 100;

    FSM::StateMachine<NpcContext> fsm;
    //sf::RectangleShape shape;
public:
    NpcContext context{};
    //Sniper() : shape({ 30.f, 30.f }) {
    //    shape.setFillColor(sf::Color::Green);
    //    shape.setPosition({ -10.f, -10.f });
    //    context.npcShape = &shape;
    //}
    //sf::RectangleShape& getShape() { return shape; }
    void Init()
    {
        PatrolState* patrolState = fsm.CreateState<PatrolState>();
        FleeState* fleeState = fsm.CreateState<FleeState>();
        AimState* aimState = fsm.CreateState<AimState>();
        ShootState* shootState = fsm.CreateState<ShootState>();

        patrolState->AddTransition(Conditions::IsSeeingPlayer, aimState);
        aimState->AddTransition(Conditions::IsTooClose, fleeState);
        aimState->AddTransition(Conditions::IsAimingFinished, shootState);
        aimState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsSeeingPlayer(_context);
            }, patrolState);
        fleeState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsTooClose(_context);
            }, aimState);
        shootState->AddTransition([](const NpcContext _ctx) {
            return true;
            }, aimState);
        fsm.Init(patrolState, context);
    }
    void Update()
    {
        fsm.Update(context);
    }
};
