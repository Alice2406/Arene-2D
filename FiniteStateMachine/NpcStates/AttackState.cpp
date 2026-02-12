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

        // ✅ Timings différents selon le type d'ennemi
        float hitboxStart = HITBOX_START;
        float hitboxEnd = HITBOX_END;

        // Ajuster selon le type
        if (_context.berserker)
        {
            switch (_context.berserker->m_skinType)
            {
            case BerserkerSkin::BEAR:
                hitboxStart = 0.3f;
                hitboxEnd = 0.7f;
                break;
            case BerserkerSkin::LANCER:
                hitboxStart = 0.2f;  // Spin rapide
                hitboxEnd = 0.6f;
                break;
            case BerserkerSkin::THIEF:
                hitboxStart = 0.15f;  // Attaque très rapide
                hitboxEnd = 0.35f;
                break;
            case BerserkerSkin::TROLL:
                hitboxStart = 0.35f;  // Attaque lente
                hitboxEnd = 0.8f;
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
                hitboxStart = 0.45f;  // Frames 3-5 (épée sortie)
                hitboxEnd = 0.75f;
                break;
            case TankSkin::TURTLE:
                hitboxStart = 0.9f;  // Marteau plus lent
                hitboxEnd = 1.35f;
                break;
            case TankSkin::PANDA:
                hitboxStart = 0.9f;  // Spin 360°
                hitboxEnd = 1.65f;
                break;
            case TankSkin::MINOTAUR:
                hitboxStart = 0.9f;
                hitboxEnd = 1.5f;
                break;
            }
        }

        // ✅ Activer selon les timings calculés
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
        }
    }
}