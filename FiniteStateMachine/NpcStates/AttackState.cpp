#include "AttackState.h"
#include "../NPC/Berserker.h"
#include "../NPC/BerserkerData.h"
#include "../NPC/Tank.h"

namespace NpcAi
{
    void AttackState::Enter(NpcContext& _context)
    {
        if (_context.animator)
        {
            _context.animator->SwitchAnimation("Attack");
        }

        m_attackTimer = 0.0f;
    }

    void AttackState::Execute(NpcContext& _context)
    {
        m_attackTimer += _context.deltaTime;

        if (m_attackTimer >= HITBOX_START && m_attackTimer <= HITBOX_END)
        {
            ActivateHitboxes(_context);
        }
        else
        {
            DeactivateHitboxes(_context);
        }
    }

    void AttackState::Exit(NpcContext& _context)
    {
        DeactivateHitboxes(_context);
    }

    void AttackState::ActivateHitboxes(NpcContext& _context)
    {
        if (_context.berserker)
        {
            _context.berserker->hitbox.isActive = true;

            if (_context.berserker->m_skinType == BerserkerSkin::LANCER)
            {
                _context.berserker->hitbox2.isActive = true;
            }
        }

        if (_context.tank)
        {
            _context.tank->hitbox.isActive = true;

            // Si c'est un Panda, activer la 2ème hitbox
            if (_context.tank->m_skinType == TankSkin::PANDA)
            {
                _context.tank->hitbox2.isActive = true;
            }
        }
    }

    void AttackState::DeactivateHitboxes(NpcContext& _context)
    {
        if (_context.berserker)
        {
            _context.berserker->hitbox.isActive = false;

            if (_context.berserker->m_skinType == BerserkerSkin::LANCER)
            {
                _context.berserker->hitbox2.isActive = false;
            }
        }

        if (_context.tank)
        {
            _context.tank->hitbox.isActive = false;

            if (_context.tank->m_skinType == TankSkin::PANDA)
            {
                _context.tank->hitbox2.isActive = false;
            }
        }
    }
}