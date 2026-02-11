#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ChaseState.h"
#include "../NpcStates/AttackState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
#include "BerserkerDataBase.h"
#include "../Animation-Assets/ResourceManager.h"

using namespace NpcAi;

class Berserker
{
private:
    int value = 100;
    int m_currentHealth;
    float m_flashTimer = 0.0f;
    const float FLASH_DURATION = 0.15f;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    BerserkerData m_data;
    FSM::StateMachine<NpcContext> fsm;
public:
    NpcContext context{};
    Berserker(BerserkerSkin skinType, sf::Texture &texture) : m_sprite(m_texture), m_animator(m_sprite)
    {
         m_data = BerserkerDatabase::GetData(skinType);
         m_sprite.setTexture(texture);
         context.npcSprite = &m_sprite;
         context.animator = &m_animator;
         context.speed = m_data.moveSpeed;

         sf::Texture& texIdle = m_resources.GetTexture(m_data.idle.texturePath);
         sf::Texture& texWalk = m_resources.GetTexture(m_data.walk.texturePath);
         sf::Texture& texAttack = m_resources.GetTexture(m_data.attack.texturePath);

         m_animator.AddAnimation("Idle", texIdle, m_data.idle.frameSize, m_data.idle.frameCount, m_data.idle.speed);
         m_animator.AddAnimation("Walk", texWalk, m_data.walk.frameSize, m_data.walk.frameCount, m_data.walk.speed);
         m_animator.AddAnimation("Attack", texAttack, m_data.attack.frameSize, m_data.attack.frameCount, m_data.attack.speed);
         m_sprite.setOrigin({ m_data.idle.frameSize.x / 2.f, m_data.idle.frameSize.y / 2.f });
         m_currentHealth = m_data.health;
         m_animator.SwitchAnimation("Idle");
    }
    void Init();
    void setPosition(const sf::Vector2f& position);
    sf::Sprite& getSprite();
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

    void Draw(sf::RenderWindow& window);

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
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
};
