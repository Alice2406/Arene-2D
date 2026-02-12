#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "../NPC/EnemyProjectile.h"
#include "SFML/Graphics.hpp"
#include <iostream>

namespace NpcAi
{
    class ShootState : public FSM::State<NpcContext>
    {
    public:
        void Enter(NpcContext& _context) override
        {
            if (_context.animator) _context.animator->SwitchAnimation("Attack");
            if (_context.projectileList && _context.weaponTexture)
            {
                sf::Vector2f startPos = _context.npcSprite->getPosition();

                EnemyProjectile* newProj = new EnemyProjectile(
                    *_context.weaponTexture,
                    _context.weaponConfig,
                    startPos,
                    _context.playerPos
                );

                _context.projectileList->push_back(newProj);
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