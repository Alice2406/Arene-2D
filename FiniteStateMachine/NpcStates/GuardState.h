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
            std::cout << "Bouclier" << std::endl;
            _context.npcShape->setFillColor(sf::Color::Red);
        }

        void Execute(NpcContext& _context) override
        {
        }

        void Exit(NpcContext& _context) override
        {
            _context.npcShape->setFillColor(sf::Color::Cyan);
        }
    };
}
