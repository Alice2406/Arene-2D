#pragma once
#include <SFML/Graphics.hpp>
#include "../Animation-Assets/Animator.h"
#include "../Animation-Assets/SharedData.h"
#include <cmath>

class EnemyProjectile
{
private:
    sf::Sprite m_sprite;
    Animator m_animator;
    sf::Texture m_texture;
    sf::Vector2f m_direction;
    sf::Vector2f m_targetPos;
    float m_speed;
    bool m_active = true;

public:
    EnemyProjectile(sf::Texture& texture, const AnimConfig& config, sf::Vector2f startPos, sf::Vector2f targetPos)
        : m_sprite(m_texture), m_animator(m_sprite), m_speed(350.0f), m_targetPos(targetPos) 
    {
        m_sprite.setPosition(startPos);

        sf::Vector2f diff = targetPos - startPos;
        float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);

        if (length != 0)
            m_direction = diff / length;
        else
            m_direction = { 1, 0 };

        m_animator.AddAnimation("Travel", texture, config.frameSize, config.frameCount, config.speed, true);
        m_animator.SwitchAnimation("Travel");

        m_sprite.setOrigin({ config.frameSize.x / 2.f, config.frameSize.y / 2.f });

        float angle = std::atan2(m_direction.y, m_direction.x) * 180 / 3.14159f;
        m_sprite.setRotation(sf::degrees(angle));
    }

    void Update(float dt)
    {
        if (!m_active) return;

        sf::Vector2f toTarget = m_targetPos - m_sprite.getPosition();
        float distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

        float moveStep = m_speed * dt;

        if (distance <= moveStep)
        {
            m_sprite.setPosition(m_targetPos);

            Destroy(); 
        }
        else
        {
            m_sprite.move(m_direction * moveStep);
        }

        m_animator.Update(dt);
    }

    void Draw(sf::RenderWindow& window) { window.draw(m_sprite); }
    sf::FloatRect GetGlobalBounds() const { return m_sprite.getGlobalBounds(); }
    bool IsActive() const { return m_active; }
    void Destroy() { m_active = false; }
};