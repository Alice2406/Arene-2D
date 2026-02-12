#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "../NPC/EnemyProjectile.h"
#include "../NPC/SniperData.h"
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

            if (_context.projectileList && _context.weaponTexture && _context.sniperData)
            {
                sf::Vector2f startPos = _context.npcSprite->getPosition();
                sf::Vector2f direction = _context.playerPos - startPos;

                const SniperData* data = _context.sniperData;

                EnemyProjectile* newProj = new EnemyProjectile(
                    *_context.weaponTexture,
                    startPos,
                    direction,
                    data->projectileSpeed,
                    _context.weaponConfig.frameSize,
                    data->projectileDamage,
                    _context.ownerSniper,
                    _context.weaponConfig.frameCount,
                    _context.weaponConfig.speed,
                    data->projectileHitboxSize,
                    data->projectileHitboxOffset
                );

                _context.projectileList->push_back(newProj);

                std::cout << "Sniper tire ! (Vitesse: " << data->projectileSpeed
                    << ", Degats: " << data->projectileDamage << ")" << std::endl;
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