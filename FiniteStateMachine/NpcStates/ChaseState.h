#pragma once
#include <iostream>
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"

namespace NpcAi
{
    class ChaseState : public FSM::State<NpcContext>
    {
        void Enter(NpcContext& _context) override
        {
            std::cout << "Enter Chase _State" << std::endl;
            _context.npcShape->setFillColor(sf::Color::Magenta);
        }

        void Execute(NpcContext& _context) override
        {
            sf::Vector2f direction = _context.playerPos - _context.npcShape->getPosition();

            float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

            if (length > 0)
            {
                direction.x /= length;
                direction.y /= length;

            }

            _context.npcShape->move(direction * _context.speed * _context.deltaTime);
        }
        void Exit(NpcContext& _context) override
        {
            std::cout << "Exit Chase _State" << std::endl;
            _context.npcShape->setFillColor(sf::Color::Red);
        }
    };
}
