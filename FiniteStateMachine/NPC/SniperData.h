#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

enum class SniperSkin {
    GNOLL,
    HARPOONFISH,
    SHAMAN
};

struct AnimConfig {
    std::string texturePath;
    sf::Vector2i frameSize;
    int frameCount;
    float speed;
};

struct SniperData {
    float moveSpeed;
    int health;
    sf::Vector2f scale;

    AnimConfig idle;
    AnimConfig walk;
    AnimConfig attack;
    AnimConfig weapon;
};