#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
#include <iostream>

// ✅ Forward declarations seulement
class Berserker;
class Tank;
enum class BerserkerSkin;

namespace NpcAi
{
    class AttackState : public FSM::State<NpcContext>
    {
    private:
        float m_attackTimer = 0.0f;
        const float HITBOX_START = 0.2f;
        const float HITBOX_END = 0.5f;

    public:
        void Enter(NpcContext& _context) override;
        void Execute(NpcContext& _context) override;
        void Exit(NpcContext& _context) override;

    private:
        void ActivateHitboxes(NpcContext& _context);
        void DeactivateHitboxes(NpcContext& _context);
    };
}