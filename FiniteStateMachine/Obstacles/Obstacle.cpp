#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture& texture, sf::Vector2f position)
    : m_sprite(texture)
{
    m_sprite.setPosition(position);

    sf::FloatRect bounds = m_sprite.getLocalBounds();

    m_sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

}

void Obstacle::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Obstacle::GetHitbox() const
{
    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    float hitH = bounds.size.y * 0.3f;

    sf::Vector2f pos = {
        bounds.position.x + 5.f,
        bounds.position.y + bounds.size.y - hitH
    };

    sf::Vector2f size = {
        bounds.size.x - 10.f,
        hitH
    };

    return sf::FloatRect(pos, size);
}