#include "EnemyProjectile.h"
EnemyProjectile::EnemyProjectile(sf::Texture& texture, const AnimConfig& config, sf::Vector2f startPos, sf::Vector2f targetPos) 
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

void EnemyProjectile::Draw(sf::RenderWindow& window) 
{ 
    window.draw(m_sprite); 
}

sf::FloatRect EnemyProjectile::GetGlobalBounds() const 
{ 
    return m_sprite.getGlobalBounds(); 
}

bool EnemyProjectile::IsActive() const 
{ 
    return m_active; 
}

void EnemyProjectile::Destroy() 
{ 
    m_active = false; 
}

sf::Vector2f EnemyProjectile::getPosition() const 
{ 
    return m_sprite.getPosition(); 
}