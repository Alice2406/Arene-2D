#pragma once
#include <iostream>
#include <ostream>
#include <cstdlib>
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
namespace NpcAi
{
    class PatrolState : public FSM::State<NpcContext>
    {
    private:
        sf::Vector2f targetpos;
        void PickNewDestination()
        {
            float x = static_cast<float>(rand() % 1900);
            float y = static_cast<float>(rand() % 800);
            targetpos = sf::Vector2f(x, y);
            std::cout << "Nouvelle cible : " << x << ", " << y << std::endl;
        }
    public:
        void Enter(NpcContext& _context) override
        {
            if (_context.animator)
            {
                _context.animator->SwitchAnimation("Walk");
            }
            if (_context.npcSprite->getPosition() == sf::Vector2f(-10.f, -10.f))
            {
                float i = rand() % 1900;
                float j = rand() % 800;
                _context.npcSprite->setPosition({ i, j });
            }
            std::cout << "Enter Patrol _State" << std::endl;
            PickNewDestination();
        }
        void Execute(NpcContext& _context) override
        {
            sf::Vector2f currentPos = _context.npcSprite->getPosition();
            sf::Vector2f direction = targetpos - currentPos;
            if (direction.x < 0)
            {
                _context.npcSprite->setScale({ -1.f, 1.f });
            }
            // Sinon, s'il est à droite
            else if (direction.x > 0)
            {
                _context.npcSprite->setScale({ 1.f, 1.f });
            }
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance < 5.0f)
                PickNewDestination();
            else
            {
                sf::Vector2f normalizedDir = direction / distance;
                _context.npcSprite->move(normalizedDir * _context.speed * _context.deltaTime);
            }
        }
        void Exit(NpcContext& _context) override
        {
            std::cout << "Exit Patrol _State" << std::endl;
        }
    };
}
