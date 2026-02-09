#include "Animator.h"

void Animator::AddAnimation(const std::string& name, sf::Texture& texture, sf::Vector2i frameSize, int count, float speed, bool loop)
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

void Animator::SwitchAnimation(const std::string& name)
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

void Animator::Update(float dt)
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