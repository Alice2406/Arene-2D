#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>

class Animator
{
public:
    struct Animation
    {
        const sf::Texture* texture;
        std::vector<sf::IntRect> frames;
        float duration;
        bool looping;
    };

private:
    sf::Sprite& m_sprite;
    std::map<std::string, Animation> m_animations;
    Animation* m_currentAnim = nullptr;
    std::string m_currentAnimName;

    float m_timer = 0.0f;
    int m_currentFrameIndex = 0;

public:
    explicit Animator(sf::Sprite& sprite) : m_sprite(sprite) {}
    void AddAnimation(const std::string& name, sf::Texture& texture, sf::Vector2i frameSize, int count, float speed, bool loop = true);
    void SwitchAnimation(const std::string& name);
    void Update(float dt);
};