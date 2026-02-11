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
        sf::Vector2f m_lastPosition;
        float m_stuckTimer;
        sf::Vector2f GetRandomPos(sf::Vector2f bounds)
        {
            if (bounds.x < 100.f || bounds.y < 100.f)
            {
                std::cout << "[ERREUR] worldBounds est vide (0,0) !" << std::endl;
                targetpos = sf::Vector2f(200.f, 200.f);
                return targetpos;
            }
            float x = static_cast<float>(rand() % (int)bounds.x);
            float y = static_cast<float>(rand() % (int)bounds.y);
            return sf::Vector2f(x, y);
        }

        void PickNewDestination(NpcContext& _context) 
        {
            targetpos = GetRandomPos(_context.worldBounds);
            std::cout << "Nouvelle cible : " << targetpos.x << ", " << targetpos.y << std::endl;
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
                _context.npcSprite->setPosition(GetRandomPos(_context.worldBounds));
            }
            std::cout << "Enter Patrol _State" << std::endl;
            PickNewDestination(_context);
            m_stuckTimer = 0.0f;
            m_lastPosition = _context.npcSprite->getPosition();
        }
        void Execute(NpcContext& _context) override
        {
            m_stuckTimer += _context.deltaTime;

            if (m_stuckTimer >= 1.0f)
            {
                sf::Vector2f currentPos = _context.npcSprite->getPosition();

                float dx = currentPos.x - m_lastPosition.x;
                float dy = currentPos.y - m_lastPosition.y;
                float movedDistance = std::sqrt(dx * dx + dy * dy);

                if (movedDistance < 10.0f)
                {
                    PickNewDestination(_context);
                    m_stuckTimer = 0.0f;
                    m_lastPosition = _context.npcSprite->getPosition();
                    return; 
                }
                m_stuckTimer = 0.0f;
                m_lastPosition = currentPos;
            }
            sf::Vector2f currentPos = _context.npcSprite->getPosition();
            sf::Vector2f direction = targetpos - currentPos;
            if (direction.x < 0)
            {
                _context.npcSprite->setScale({ -_context.baseScale.x, _context.baseScale.y });
            }
            else if (direction.x > 0)
            {
                _context.npcSprite->setScale({ _context.baseScale.x, _context.baseScale.y });
            }
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance < 5.0f)
                PickNewDestination(_context);
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
