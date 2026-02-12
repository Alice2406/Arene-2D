#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Core/CollisionBox.h"
#include "../Core/CollisionManager.h"

class EnemyProjectile : public IDestructible
{
private:
    sf::Sprite m_sprite;
    const sf::Texture* m_texture;
    sf::Vector2f m_velocity;
    bool m_isActive;
    float m_lifetime;
    const float MAX_LIFETIME = 5.0f;
    float m_damage;

public:
    CollisionBox hitbox;

    EnemyProjectile(
        const sf::Texture& texture,
        sf::Vector2f position,
        sf::Vector2f direction,
        float speed,
        sf::Vector2i frameSize,
        float damage = 10.0f
    )
        : m_sprite(texture),
        m_texture(&texture),
        m_velocity(),
        m_isActive(true),
        m_lifetime(0.0f),
        m_damage(damage),
        hitbox(sf::Vector2f(frameSize.x * 0.6f, frameSize.y * 0.6f), sf::Vector2f(0.f, 0.f))
    {
        m_sprite.setPosition(position);

        sf::IntRect textureRect(sf::Vector2i(0, 0), frameSize);
        m_sprite.setTextureRect(textureRect);

        m_sprite.setOrigin(sf::Vector2f(frameSize) / 2.f);

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            m_velocity = sf::Vector2f(
                (direction.x / length) * speed,
                (direction.y / length) * speed
            );

            float angleDegrees = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
            m_sprite.setRotation(sf::degrees(angleDegrees));
        }
        else
        {
            m_velocity = sf::Vector2f(speed, 0.f);
        }

        hitbox.owner = this;
        hitbox.isActive = true;
    }

    void Update(float dt)
    {
        if (!m_isActive) return;

        m_sprite.setPosition(m_sprite.getPosition() + m_velocity * dt);
        hitbox.Update(m_sprite.getPosition(), 1.0f);

        m_lifetime += dt;

        if (m_lifetime >= MAX_LIFETIME)
        {
            Destroy();
        }
    }

    void Draw(sf::RenderWindow& window)
    {
        if (m_isActive)
        {
            window.draw(m_sprite);
            hitbox.debugDraw(window);
        }
    }

    bool IsActive() const
    {
        return m_isActive;
    }

    void Destroy() override
    {
        m_isActive = false;
        hitbox.isActive = false;
    }

    sf::Vector2f getPosition() const
    {
        return m_sprite.getPosition();
    }

    float getDamage() const
    {
        return m_damage;
    }
};