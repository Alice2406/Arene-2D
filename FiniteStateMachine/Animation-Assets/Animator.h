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

    void AddAnimation(const std::string& name, sf::Texture& texture, sf::Vector2i frameSize, int count, float speed, bool loop = true)
    {
        Animation anim;
        anim.texture = &texture;
        anim.duration = speed;
        anim.looping = loop;

        for (int i = 0; i < count; ++i)
        {
            sf::Vector2i pos(i * frameSize.x, 0);
            sf::Vector2i size(frameSize.x, frameSize.y);
            anim.frames.emplace_back(pos, size);
        }

        m_animations[name] = anim;
    }

    void SwitchAnimation(const std::string& name)
    {
        if (m_currentAnimName == name) return;

        auto it = m_animations.find(name);
        if (it == m_animations.end()) return;

        m_currentAnimName = name;
        m_currentAnim = &it->second;
        m_currentFrameIndex = 0;
        m_timer = 0.0f;

        if (m_currentAnim->texture)
        {
            m_sprite.setTexture(*m_currentAnim->texture);
        }

        if (!m_currentAnim->frames.empty())
        {
            m_sprite.setTextureRect(m_currentAnim->frames[0]);
        }
    }

    void Update(float dt)
    {
        if (!m_currentAnim) return;

        m_timer += dt;

        if (m_timer >= m_currentAnim->duration)
        {
            m_timer = 0.0f;
            m_currentFrameIndex++;

            if (m_currentFrameIndex >= m_currentAnim->frames.size())
            {
                if (m_currentAnim->looping)
                {
                    m_currentFrameIndex = 0;
                }
                else
                {
                    m_currentFrameIndex = (int)m_currentAnim->frames.size() - 1;
                }
            }

            m_sprite.setTextureRect(m_currentAnim->frames[m_currentFrameIndex]);
        }
    }
};