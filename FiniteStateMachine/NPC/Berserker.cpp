#include "Berserker.h"

Berserker::Berserker(BerserkerSkin skinType, sf::Texture& texture) : m_sprite(m_texture), m_animator(m_sprite)
{
    m_data = BerserkerDatabase::GetData(skinType);
    m_sprite.setTexture(texture);
    context.npcSprite = &m_sprite;
    context.animator = &m_animator;
    context.speed = m_data.moveSpeed;
    context.berserker = this;

    sf::Texture& texIdle = m_resources.GetTexture(m_data.idle.texturePath);
    sf::Texture& texWalk = m_resources.GetTexture(m_data.walk.texturePath);
    sf::Texture& texAttack = m_resources.GetTexture(m_data.attack.texturePath);

    m_animator.AddAnimation("Idle", texIdle, m_data.idle.frameSize, m_data.idle.frameCount, m_data.idle.speed);
    m_animator.AddAnimation("Walk", texWalk, m_data.walk.frameSize, m_data.walk.frameCount, m_data.walk.speed);
    m_animator.AddAnimation("Attack", texAttack, m_data.attack.frameSize, m_data.attack.frameCount, m_data.attack.speed);
    m_sprite.setOrigin({ m_data.idle.frameSize.x / 2.f, m_data.idle.frameSize.y / 2.f });
    m_animator.SwitchAnimation("Idle");

    hurtbox = CollisionBox(m_data.hurtboxSize, m_data.hurtboxOffset);
    hurtbox.owner = this;
    hurtbox.isActive = true;
    hurtbox.isPlayer = false;

    hitbox = CollisionBox(m_data.hitboxSize, m_data.hitboxOffset);
    hitbox.owner = this;
    hitbox.isActive = false;
    hitbox.damage = m_data.attackDamage;

    health = HealthComponent(m_data.health);
}

//FSM Berserker
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
    hurtbox.debugDraw(window);
    hitbox.debugDraw(window);
}

void Berserker::handleDamage(float amount)
{
        if (health.IsDead()) return;

        health.takeDamage(amount);

        m_sprite.setColor(sf::Color(255, 100, 100));
        m_flashTimer = FLASH_DURATION;
}

bool Berserker::IsDead() const
{
        return health.IsDead();
}

void Berserker::Update(float dt)
{
    fsm.Update(context);
    m_animator.Update(dt);
    hurtbox.Update(m_sprite.getPosition(), m_sprite.getScale().x);
    hitbox.Update(m_sprite.getPosition(), m_sprite.getScale().x);
    if (m_flashTimer > 0)
    {
        m_flashTimer -= dt;
        if (m_flashTimer <= 0)
        {
            m_sprite.setColor(sf::Color::White);
        }
    }
}

bool Berserker::IsHit() const
{
    return m_flashTimer > 0.0f;
}
