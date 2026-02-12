#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include "../Animation-Assets/SharedData.h"

enum class BerserkerSkin {
    BEAR,
    GNOME,
    LANCER,
    PADDLEFISH,
    THIEF,
    TROLL,
    COUNT,
};

struct BerserkerData {
    float moveSpeed;
    int health;
    sf::Vector2f scale;

    AnimConfig idle;
    AnimConfig walk;
    AnimConfig attack;
    AnimConfig guard;

    sf::Vector2f hurtboxSize;
    sf::Vector2f hurtboxOffset;
    sf::Vector2f hitboxSize;
    sf::Vector2f hitboxOffset;
    sf::Vector2f hitbox2Size;
    sf::Vector2f hitbox2Offset;

    float attackDamage;
};