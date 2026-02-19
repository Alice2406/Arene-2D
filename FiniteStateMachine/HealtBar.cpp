#include "HealthBar.h"

HealthBar::HealthBar(sf::Vector2f size, sf::Vector2f position)
    : m_size(size), m_position(position), m_maxHealth(100.f), m_currentHealth(100.f)
{
    m_background.setSize(m_size);
    m_background.setFillColor(sf::Color(50, 50, 50));
    m_background.setPosition(m_position);

    m_healthBar.setSize(m_size);
    m_healthBar.setFillColor(sf::Color(200, 50, 50));
    m_healthBar.setPosition(m_position);

    m_border.setSize(m_size);
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Black);
    m_border.setOutlineThickness(3.f);
    m_border.setPosition(m_position);
}

void HealthBar::Update(float currentHealth, float maxHealth)
{
    m_currentHealth = currentHealth;
    m_maxHealth = maxHealth;

    float healthPercent = m_currentHealth / m_maxHealth;
    if (healthPercent < 0.f) healthPercent = 0.f;
    if (healthPercent > 1.f) healthPercent = 1.f;

    m_healthBar.setSize({ m_size.x * healthPercent, m_size.y });

    if (healthPercent > 0.6f)
        m_healthBar.setFillColor(sf::Color(100, 200, 100));
    else if (healthPercent > 0.3f)
        m_healthBar.setFillColor(sf::Color(255, 200, 50));
    else
        m_healthBar.setFillColor(sf::Color(200, 50, 50));
}

void HealthBar::SetPosition(sf::Vector2f position)
{
    m_position = position;
    m_background.setPosition(m_position);
    m_healthBar.setPosition(m_position);
    m_border.setPosition(m_position);
}

void HealthBar::Draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_healthBar);
    window.draw(m_border);
}