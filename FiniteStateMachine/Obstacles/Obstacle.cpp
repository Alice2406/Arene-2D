#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType type, const sf::Texture& texture, sf::Vector2f position)
    : m_sprite(texture), m_type(type), m_timer(0.f), m_currentFrame(0)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

    m_hitboxWidthScale = 0.6f;
    m_hitboxHeightScale = 1.f;
    m_hitboxOffsetY = 0.f;

    switch (type)
    {
    case ObstacleType::ROCK1:
        m_isSolid = true;
        m_isAnimated = false;
        break;
	case ObstacleType::ROCK2:
        m_isSolid = true;
        m_isAnimated = false;
        break;
	case ObstacleType::ROCK3:
        m_isSolid = true;
        m_isAnimated = false;
        break;
	case ObstacleType::ROCK4:
        m_isSolid = true;
        m_isAnimated = false;
        break;
    case ObstacleType::TREE:
        m_isSolid = true;
        m_isAnimated = false;
        break;
	case ObstacleType::SHEEP1:
        m_isSolid = true;
        m_isAnimated = true;
        m_hitboxWidthScale = 0.3f;
        m_hitboxHeightScale = 0.2f;
        m_hitboxOffsetY = -55.f;
        m_frameCount = 12;   
        m_frameTime = 0.15f;   
        m_frameSize = { 128, 128 };
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameSize.x, m_frameSize.y }));
		break;
    case ObstacleType::SHEEP2:
        m_isSolid = true;
        m_isAnimated = true;
        m_frameCount = 6;
        m_hitboxWidthScale = 0.3f;
        m_hitboxHeightScale = 0.2f;
        m_hitboxOffsetY = -55.f;
        m_frameTime = 0.15f;  
        m_frameSize = { 128, 128 }; 
		m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameSize.x, m_frameSize.y }));
        break;
	case ObstacleType::BUSHE1:
        m_isSolid = true;
		m_isAnimated = true;
        m_frameCount = 8;
        m_hitboxWidthScale = 0.3f;
        m_hitboxHeightScale = 0.2f;
        m_hitboxOffsetY = -55.f;
        m_frameTime = 0.2f; 
		m_frameSize = { 128, 128 }; 
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameSize.x, m_frameSize.y }));
		break;
	case ObstacleType::BUSHE2:
        m_isSolid = false;
        m_isAnimated = true;
        m_frameCount = 8;   
        m_frameTime = 0.2f; 
        m_frameSize = { 128, 128 }; 
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameSize.x, m_frameSize.y }));
        break;
    case ObstacleType::BUSHE3:
        m_isSolid = false;
        m_isAnimated = true;
        m_frameCount = 8;   
        m_frameTime = 0.2f; 
        m_frameSize = { 128, 128 };
        m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { m_frameSize.x, m_frameSize.y }));
		break;
    }
}

void Obstacle::Update(float dt)
{
    if (!m_isAnimated) return;

    m_timer += dt;
    if (m_timer >= m_frameTime)
    {
        m_timer = 0.f;
        m_currentFrame++;

        if (m_currentFrame >= m_frameCount)
            m_currentFrame = 0;

        int left = m_currentFrame * m_frameSize.x;
        m_sprite.setTextureRect(sf::IntRect({ left, 0 }, { m_frameSize.x, m_frameSize.y }));
    }
}

sf::FloatRect Obstacle::GetHitbox() const
{
    if (!m_isSolid) return sf::FloatRect({ 0, 0 }, { 0, 0 });

    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    float hitWidth = bounds.size.x * m_hitboxWidthScale;  
    float hitHeight = bounds.size.y * m_hitboxHeightScale;

    float hitX = bounds.position.x + (bounds.size.x - hitWidth) / 2.f;

    float hitY = bounds.position.y + bounds.size.y - hitHeight + m_hitboxOffsetY;

    return sf::FloatRect({ hitX, hitY }, { hitWidth, hitHeight });
}

void Obstacle::Draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Obstacle::DebugDraw(sf::RenderWindow& window)
{
    if (!m_isSolid) return;

    sf::FloatRect hit = GetHitbox();

    sf::RectangleShape debugBox({ hit.size.x, hit.size.y });
    debugBox.setPosition(hit.position);

    debugBox.setFillColor(sf::Color::Transparent);
    debugBox.setOutlineColor(sf::Color::Red);
    debugBox.setOutlineThickness(1.f);

    window.draw(debugBox);
}