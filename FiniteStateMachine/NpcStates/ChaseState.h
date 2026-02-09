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
            if (_context.animator)
            {
                _context.animator->SwitchAnimation("Walk");
            }
        }

        void Execute(NpcContext& _context) override
        {
            sf::Vector2f direction = _context.playerPos - _context.npcSprite->getPosition();
            if (direction.x < 0)
            {
                _context.npcSprite->setScale({ -1.f, 1.f });
            }
            else if (direction.x > 0)
            {
                _context.npcSprite->setScale({ 1.f, 1.f });
            }
            float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

            if (length > 0)
            {
                direction.x /= length;
                direction.y /= length;

            }

            _context.npcSprite->move(direction * _context.speed * _context.deltaTime);
        }
        void Exit(NpcContext& _context) override
        {
            std::cout << "Exit Chase _State" << std::endl;
        }
    };
}
