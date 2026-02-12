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
    explicit EnemyProjectile(sf::Texture& texture, const AnimConfig& config, sf::Vector2f startPos, sf::Vector2f targetPos);

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

    void Draw(sf::RenderWindow& window);
    sf::FloatRect GetGlobalBounds() const;
    bool IsActive() const;
    void Destroy();
    sf::Vector2f getPosition() const;
};