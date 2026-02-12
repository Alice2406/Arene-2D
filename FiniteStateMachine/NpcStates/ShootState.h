#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "../NPC/EnemyProjectile.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace NpcAi
{
    class ShootState : public FSM::State<NpcContext>
    {
    public:
        void Enter(NpcContext& _context) override
        {
            if (_context.animator)
            {
                _context.animator->SwitchAnimation("Attack");
            }

            if (_context.projectileList && _context.weaponTexture)
            {
                sf::Vector2f startPos = _context.npcSprite->getPosition();
                sf::Vector2f direction = _context.playerPos - startPos;

                float speed = 300.0f;
                float damage = 15.0f;

                sf::Vector2i frameSize = _context.weaponConfig.frameSize;

                if (frameSize.x >= 128)
                {
                    speed = 250.0f;
                    damage = 25.0f;
                }
                else if (frameSize.x == 64)
                {
                    speed = 400.0f;
                    damage = 12.0f;
                }

                EnemyProjectile* newProj = new EnemyProjectile(
                    *_context.weaponTexture,
                    startPos,
                    direction,
                    speed,
                    frameSize,
                    damage
                );

                _context.projectileList->push_back(newProj);

                std::cout << "Sniper tire ! (Vitesse: " << speed << ", Degats: " << damage << ")" << std::endl;
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