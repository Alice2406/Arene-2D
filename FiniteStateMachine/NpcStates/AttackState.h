#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
#include <iostream>

namespace NpcAi
{
    class AttackState : public FSM::State<NpcContext>
    {
    public:
        void Enter(NpcContext& _context) override
        {
            std::cout << "ATTACK !!!" << std::endl;
            if (_context.animator)
            {
                _context.animator->SwitchAnimation("Attack");
            }
        }

        void Execute(NpcContext& _context) override
        {
        }

        void Exit(NpcContext& _context) override
        {
        }
    };
}