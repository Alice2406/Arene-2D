#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include "../Animation-Assets/SharedData.h"

enum class SniperSkin {
    GNOLL,
    HARPOONFISH,
    SHAMAN,
    COUNT,
};

struct SniperData {
    float moveSpeed;
    int health;
    sf::Vector2f scale;

    AnimConfig idle;
    AnimConfig walk;
    AnimConfig attack;
    AnimConfig weapon;

    sf::Vector2f hurtboxSize;
    sf::Vector2f hurtboxOffset;

    sf::Vector2f projectileHitboxSize;
    sf::Vector2f projectileHitboxOffset;
    float projectileSpeed;
    float projectileDamage;
};