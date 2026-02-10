#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ShootState.h"
#include "../NpcStates/FleeState.h"
#include "../NpcStates/AimState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
#include "SniperDataBase.h"

using namespace NpcAi;


class Sniper
{
private:
    int value = 100;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    SniperData m_data;
    int m_currentHealth;
    float m_flashTimer = 0.0f;
    const float FLASH_DURATION = 0.15f;
    FSM::StateMachine<NpcContext> fsm;
public:
    NpcContext context{};
    Sniper(SniperSkin skinType) : m_sprite(m_texture), m_animator(m_sprite)
    {
        m_data = SniperDatabase::GetData(skinType);

        context.npcSprite = &m_sprite;
        context.animator = &m_animator;
        context.speed = m_data.moveSpeed;
        sf::Texture& texIdle = m_resources.GetTexture(m_data.idle.texturePath);
        sf::Texture& texWalk = m_resources.GetTexture(m_data.walk.texturePath);
        sf::Texture& texAttack = m_resources.GetTexture(m_data.attack.texturePath);
        sf::Texture& texWeapon = m_resources.GetTexture(m_data.weapon.texturePath);

        context.weaponTexture = &texWeapon;
        context.weaponConfig = m_data.weapon;
        m_animator.AddAnimation("Idle", texIdle, m_data.idle.frameSize, m_data.idle.frameCount, m_data.idle.speed);
        m_animator.AddAnimation("Walk", texWalk, m_data.walk.frameSize, m_data.walk.frameCount, m_data.walk.speed);
        m_animator.AddAnimation("Attack", texAttack, m_data.attack.frameSize, m_data.attack.frameCount, m_data.attack.speed);
        m_animator.AddAnimation("Weapon", texWeapon, m_data.weapon.frameSize, m_data.weapon.frameCount, m_data.weapon.speed);
        m_sprite.setOrigin({ m_data.idle.frameSize.x / 2.f, m_data.idle.frameSize.y / 2.f });
        m_currentHealth = m_data.health;
        m_animator.SwitchAnimation("Idle");
    }
    void Init()
    {
        PatrolState* patrolState = fsm.CreateState<PatrolState>();
        FleeState* fleeState = fsm.CreateState<FleeState>();
        AimState* aimState = fsm.CreateState<AimState>();
        ShootState* shootState = fsm.CreateState<ShootState>();

        patrolState->AddTransition(Conditions::IsSeeingPlayer, aimState);
        aimState->AddTransition(Conditions::IsTooClose, fleeState);
        aimState->AddTransition(Conditions::IsAimingFinished, shootState);
        aimState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsSeeingPlayer(_context);
            }, patrolState);
        fleeState->AddTransition([](const NpcContext _context)
            {
                return !Conditions::IsTooClose(_context);
            }, aimState);
        shootState->AddTransition([](const NpcContext _ctx) {
            return true;
            }, aimState);
        fsm.Init(patrolState, context);
    }
    void setPosition(const sf::Vector2f& position)
    {
        m_sprite.setPosition(position);
    }
    sf::Sprite& getSprite() { return m_sprite; }
    void Update(float dt)
    {
        fsm.Update(context);
        m_animator.Update(dt);
        if (m_flashTimer > 0)
        {
            m_flashTimer -= dt;
            if (m_flashTimer <= 0)
            {
                m_sprite.setColor(sf::Color::White);
            }
        }
    }

    sf::FloatRect GetGlobalBounds() const { return m_sprite.getGlobalBounds(); }

    bool IsHit() const {
        return m_flashTimer > 0.0f;
    }
    void Draw(sf::RenderWindow& window)
    {
        window.draw(m_sprite);
    }

    void TakeDamage(int damageAmount)
    {
        m_currentHealth -= damageAmount;

        m_sprite.setColor(sf::Color(255, 100, 100));
        m_flashTimer = FLASH_DURATION;

        std::cout << "Aie ! Vie restante : " << m_currentHealth << std::endl;
    }

    bool IsDead() const
    {
        return m_currentHealth <= 0;
    }
};
