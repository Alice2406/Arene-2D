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
                _context.npcSprite->setScale({ -_context.baseScale.x, _context.baseScale.y });
            }
            else if (direction.x > 0)
            {
                _context.npcSprite->setScale({ _context.baseScale.x, _context.baseScale.y });
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
        }
    };
}
