#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
private:
    sf::Sprite m_sprite;
    sf::FloatRect m_hitbox;

public:
    Obstacle(sf::Texture& texture, sf::Vector2f position);

    void Draw(sf::RenderWindow& window);
    sf::FloatRect GetHitbox() const;
    sf::Vector2f GetPosition() const { return m_sprite.getPosition(); }
};