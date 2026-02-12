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
    attackState->AddTransition([attackState](const NpcContext _context)
        {
            return attackState->IsFinished();
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
    hurtbox.debugDraw(window);
    hitbox.debugDraw(window);
}

void Berserker::handleDamage(float amount)
{
    if (health.IsDead()) return;

    health.takeDamage(amount);

    m_sprite.setColor(sf::Color(255, 100, 100));
    m_flashTimer = FLASH_DURATION;

    std::cout << "Tank - Vie restante : " << health.getHealth()
        << "/" << health.getMaxHealth() << std::endl;
}