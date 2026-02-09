#pragma once
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"
#include "../NpcStates/ChaseState.h"
#include "../NpcStates/AttackState.h"
#include "../NpcStates/Conditions.h"
#include "../NpcStates/NpcContext.h"
#include "../NpcStates/PatrolState.h"
#include "BerserkerDataBase.h"
#include "../Animation-Assets/ResourceManager.h"

using namespace NpcAi;

class Berserker
{
private:
    int value = 100;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    ResourceManager m_resources;
    Animator m_animator;
    BerserkerData m_data;
    FSM::StateMachine<NpcContext> fsm;
public:
    NpcContext context{};
    Berserker(BerserkerSkin skinType) : m_sprite(m_texture), m_animator(m_sprite) {};
    void Init();
    void setPosition(const sf::Vector2f& position);
    sf::Sprite& getSprite();
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
};
