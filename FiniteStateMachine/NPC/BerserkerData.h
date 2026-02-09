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
    TROLL
};

struct BerserkerData {
    float moveSpeed;
    int health;
    sf::Vector2f scale;

    AnimConfig idle;
    AnimConfig walk;
    AnimConfig attack;
    AnimConfig guard;
};