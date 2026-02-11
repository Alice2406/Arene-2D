#pragma once
#include <SFML/Graphics.hpp>

enum class ObstacleType {
    ROCK1, //solide, obstacle
    ROCK2, //solide, obstacle
    ROCK3, //solide, obstacle
    ROCK4, //solide, obstacle
    TREE, //solide, obstacle
    SHEEP1, //anime, obstacle
	SHEEP2, //anime, obstacle
	BUSHE1, //anime, pas obstacle
	BUSHE2, //anime, pas obstacle
	BUSHE3, //anime, pas obstacle
};

class Obstacle
{
private:
    sf::Sprite m_sprite;
    ObstacleType m_type;
    bool m_isSolid;

    bool m_isAnimated;
    int m_currentFrame;
    int m_frameCount;  
    float m_frameTime; 
    float m_timer;
    sf::Vector2i m_frameSize; 

public:
    Obstacle(ObstacleType type, const sf::Texture& texture, sf::Vector2f position);

    void Update(float dt); 
    void Draw(sf::RenderWindow& window);

    sf::FloatRect GetHitbox() const;
    const sf::Sprite& GetSprite() const { return m_sprite; }
    bool IsSolid() const { return m_isSolid; } 
};