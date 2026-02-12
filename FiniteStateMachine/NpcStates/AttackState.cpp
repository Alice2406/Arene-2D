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
        m_isFinished = false;

        if (_context.berserker)
        {
            _context.berserker->hitbox.ResetHit();

            switch (_context.berserker->m_skinType)
            {
            case BerserkerSkin::BEAR:
                m_attackDuration = 9 * 0.15f;
                break;
            case BerserkerSkin::LANCER:
                m_attackDuration = 8 * 0.15f;
                break;
            case BerserkerSkin::THIEF:
                m_attackDuration = 6 * 0.15f;
                break;
            case BerserkerSkin::TROLL:
                m_attackDuration = 6 * 0.15f;
                break;
            case BerserkerSkin::PADDLEFISH:
                m_attackDuration = 6 * 0.15f;
                break;
            case BerserkerSkin::GNOME:
                m_attackDuration = 7 * 0.15f;
                break;
            default:
                m_attackDuration = 1.0f;
                break;
            }
        }

        if (_context.tank)
        {
            _context.tank->hitbox.ResetHit();

            switch (_context.tank->m_skinType)
            {
            case TankSkin::SKULL:
                m_attackDuration = 7 * 0.15f;
                break;
            case TankSkin::TURTLE:
                m_attackDuration = 10 * 0.15f;
                break;
            case TankSkin::PANDA:
                m_attackDuration = 13 * 0.15f;
                break;
            case TankSkin::MINOTAUR:
                m_attackDuration = 12 * 0.15f;
                break;
            default:
                m_attackDuration = 1.0f;
                break;
            }
        }
    }

    void AttackState::Execute(NpcContext& _context)
    {
        m_attackTimer += _context.deltaTime;

        if (m_attackTimer >= m_attackDuration)
        {
            m_isFinished = true;
            DeactivateHitboxes(_context);
            return;
        }

        float hitboxStart = HITBOX_START;
        float hitboxEnd = HITBOX_END;

        if (_context.berserker)
        {
            switch (_context.berserker->m_skinType)
            {
            case BerserkerSkin::BEAR:
                hitboxStart = 0.9f;
                hitboxEnd = 1.0f;
                break;
            case BerserkerSkin::LANCER:
                hitboxStart = 0.7f;
                hitboxEnd = 0.8f;
                break;
            case BerserkerSkin::THIEF:
                hitboxStart = 0.45f;
                hitboxEnd = 0.6f;
                break;
            case BerserkerSkin::TROLL:
                hitboxStart = 0.45f;
                hitboxEnd = 0.75f;
                break;
            case BerserkerSkin::PADDLEFISH:
                hitboxStart = 0.55f;
                hitboxEnd = 0.70f;
                break;
            case BerserkerSkin::GNOME:
                hitboxStart = 0.6f;
                hitboxEnd = 0.75f;
                break;
            default:
                break;
            }
        }

        if (_context.tank)
        {
            switch (_context.tank->m_skinType)
            {
            case TankSkin::SKULL:
                hitboxStart = 0.45f;
                hitboxEnd = 0.75f;
                break;
            case TankSkin::TURTLE:
                hitboxStart = 0.9f;
                hitboxEnd = 1.35f;
                break;
            case TankSkin::PANDA:
                hitboxStart = 0.9f;
                hitboxEnd = 1.65f;
                break;
            case TankSkin::MINOTAUR:
                hitboxStart = 0.9f;
                hitboxEnd = 1.5f;
                break;
            default:
                break;
            }
        }

        if (m_attackTimer >= hitboxStart && m_attackTimer <= hitboxEnd)
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

        if (_context.berserker)
        {
            _context.berserker->hitbox.ResetHit();
        }

        if (_context.tank)
        {
            _context.tank->hitbox.ResetHit();
        }
    }

    void AttackState::ActivateHitboxes(NpcContext& _context)
    {
        if (_context.berserker)
        {
            _context.berserker->hitbox.isActive = true;
        }

        if (_context.tank)
        {
            _context.tank->hitbox.isActive = true;
        }
    }

    void AttackState::DeactivateHitboxes(NpcContext& _context)
    {
        if (_context.berserker)
        {
            _context.berserker->hitbox.isActive = false;
        }

        if (_context.tank)
        {
            _context.tank->hitbox.isActive = false;
        }
    }
};