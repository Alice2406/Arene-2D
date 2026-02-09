#include "Berserker.h"

void Berserker::Init()
{
    PatrolState* patrolState = fsm.CreateState<PatrolState>();
    ChaseState* chaseState = fsm.CreateState<ChaseState>();
    AttackState* attackState = fsm.CreateState<AttackState>();
    patrolState->AddTransition(Conditions::IsSeeingPlayer, chaseState);
    chaseState->AddTransition(Conditions::IsInAttackRange, attackState);
    chaseState->AddTransition([](const NpcContext _context)
        {
            return !Conditions::IsSeeingPlayer(_context);
        }, patrolState);
    attackState->AddTransition([](const NpcContext _context)
        {
            return !Conditions::IsInAttackRange(_context);
        }, chaseState);
    fsm.Init(patrolState, context);
}

void Berserker::setPosition(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
}

sf::Sprite& Berserker::getSprite() 
{ 
    return m_sprite; 
}

void Berserker::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}