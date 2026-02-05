#pragma once
#include <iostream>
#include <ostream>
#include <cstdlib>
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"

namespace NpcAi
{
    class FleeState : public FSM::State<NpcContext>
    {
        void Enter(NpcContext& _context) override
        {
            _context.npcShape->setFillColor(sf::Color::Magenta);
            std::cout << "Enter Flee _State" << std::endl;
        }

        void Execute(NpcContext& _context) override
        {
            sf::Vector2f myPos = _context.npcShape->getPosition();
            sf::Vector2f direction = myPos - _context.playerPos;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length > 0)
            {
                direction /= length;

                _context.npcShape->move(direction * _context.speed * 1.5f * _context.deltaTime);
            }
        }
        void Exit(NpcContext& _context) override
        {
            std::cout << "Exit Flee _State" << std::endl;
            _context.npcShape->setFillColor(sf::Color::Green);
        }
    };
}

