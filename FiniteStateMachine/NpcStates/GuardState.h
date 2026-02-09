#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
#include <iostream>

namespace NpcAi
{
    class GuardState : public FSM::State<NpcContext>
    {
    public:
        void Enter(NpcContext& _context) override
        {
            _context.currentTimer = 0.0f;
            _context.isInvulnerable = true;
            _context.triggerGuard = false;
            std::cout << "GuardState" << std::endl;
            if (_context.animator)
            {
                _context.animator->SwitchAnimation("Guard");
            }
        }
        void Execute(NpcContext& _context) override
        {
            _context.currentTimer += _context.deltaTime;
        }

        void Exit(NpcContext& _context) override
        {
            _context.isInvulnerable = false;
        }
    };
}
