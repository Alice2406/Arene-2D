#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_healthBar;
    sf::RectangleShape m_border;

    sf::Vector2f m_size;
    sf::Vector2f m_position;

    float m_maxHealth;
    float m_currentHealth;

public:
    HealthBar(sf::Vector2f size = { 300.f, 30.f }, sf::Vector2f position = { 0.f, 0.f });

    void Update(float currentHealth, float maxHealth);
    void SetPosition(sf::Vector2f position);
    void Draw(sf::RenderWindow& window);
};