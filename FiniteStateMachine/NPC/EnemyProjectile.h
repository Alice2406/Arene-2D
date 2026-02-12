#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../Core/CollisionBox.h"
#include "../Core/CollisionManager.h"
#include "../Animation-Assets/Animator.h"

class EnemyProjectile : public IDestructible
{
private:
    sf::Sprite m_sprite;
    sf::Texture* m_texture;
    sf::Vector2f m_velocity;
    bool m_isActive;
    float m_lifetime;
    const float MAX_LIFETIME = 5.0f;
    float m_damage;
    void* m_sniperOwner;
    Animator m_animator;
    float m_rotationAngle;

public:
    CollisionBox hitbox;

    EnemyProjectile(
        sf::Texture& texture,
        sf::Vector2f position,
        sf::Vector2f direction,
        float speed,
        sf::Vector2i frameSize,
        float damage = 10.0f,
        void* sniperOwner = nullptr,
        int frameCount = 4,
        float animSpeed = 0.1f,
        sf::Vector2f hitboxSize = { 0.f, 0.f },
        sf::Vector2f hitboxOffset = { 0.f, 0.f }
    )
        : m_sprite(texture),
        m_texture(&texture),
        m_velocity(),
        m_isActive(true),
        m_lifetime(0.0f),
        m_damage(damage),
        m_sniperOwner(sniperOwner),
        m_animator(m_sprite),
        m_rotationAngle(0.f),
        hitbox(
            hitboxSize.x > 0.f ? hitboxSize : sf::Vector2f(frameSize.x * 0.6f, frameSize.y * 0.6f),
            hitboxOffset
        )
    {
        m_sprite.setPosition(position);

        m_animator.AddAnimation("Travel", texture, frameSize, frameCount, animSpeed, true);
        m_animator.SwitchAnimation("Travel");

        m_sprite.setOrigin(sf::Vector2f(frameSize) / 2.f);

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            m_velocity = sf::Vector2f(
                (direction.x / length) * speed,
                (direction.y / length) * speed
            );

            float angleDegrees = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
            m_rotationAngle = angleDegrees;
            m_sprite.setRotation(sf::degrees(angleDegrees));
        }
        else
        {
            m_velocity = sf::Vector2f(speed, 0.f);
        }

        hitbox.owner = this;
        hitbox.isActive = true;
        hitbox.isProjectile = true;
        hitbox.projectileOwner = sniperOwner;
        hitbox.damage = damage;
    }

    void Update(float dt)
    {
        if (!m_isActive) return;

        m_sprite.setPosition(m_sprite.getPosition() + m_velocity * dt);
        hitbox.Update(m_sprite.getPosition(), 1.0f, m_rotationAngle);

        m_animator.Update(dt);

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

    void* getSniperOwner() const
    {
        return m_sniperOwner;
    }
};