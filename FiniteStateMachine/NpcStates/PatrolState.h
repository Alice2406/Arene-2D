#pragma once
#include <iostream>
#include <ostream>
#include <cstdlib>
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
#include "time.h"
namespace NpcAi
{
    class PatrolState : public FSM::State<NpcContext>
    {
    private:
        sf::Vector2f targetpos;
    public:
        void Enter(NpcContext _context) override
        {
            if (_context.npcShape->getPosition() == sf::Vector2f(-10.f, -10.f))
            {
                srand(time(NULL));
                float i = rand() % 800;
                float j = rand() % 800;
                _context.npcShape->setPosition({ i, j });
            }
            std::cout << "Enter Patrol _State" << std::endl;
            
        }
        void Execute(NpcContext _context) override
        {
            srand(time(NULL));
            float i = rand() % 800;
            float j = rand() % 800;
            sf::Vector2f targetpos = sf::Vector2f(i, j);

            float length = std::sqrt((targetpos.x * targetpos.x) + (targetpos.y * targetpos.y));

            if (length > 0)
            {
                targetpos.x /= length;
                targetpos.y /= length;

            }

            _context.npcShape->move(targetpos * _context.speed * _context.deltaTime);
            
        }
        void Exit(NpcContext _context) override
        {
            std::cout << "Exit Patrol _State" << std::endl;
        }
    };
}
