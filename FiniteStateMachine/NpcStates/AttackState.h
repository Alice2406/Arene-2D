#pragma once
#include "NpcContext.h"
#include "../StateMachine/State.h"
#include "SFML/Graphics.hpp"
#include <iostream>

namespace NpcAi
{
    class AttackState : public FSM::State<NpcContext>
    {
    private:
        float m_attackTimer = 0.0f;
        float m_attackDuration = 1.0f;
        const float HITBOX_START = 0.2f;
        const float HITBOX_END = 0.5f;
        bool m_isFinished = false;

        void ActivateHitboxes(NpcContext& _context);
        void DeactivateHitboxes(NpcContext& _context);

    public:
        void Enter(NpcContext& _context) override;
        void Execute(NpcContext& _context) override;
        void Exit(NpcContext& _context) override;

        bool IsFinished() const { return m_isFinished; }
    };
}