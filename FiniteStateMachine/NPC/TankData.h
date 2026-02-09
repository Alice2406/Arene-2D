#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

enum class TankSkin {
    TURTLE,
    MINOTAUR,
    PANDA,
    SKULL
};

struct AnimConfig {
    std::string texturePath;
    sf::Vector2i frameSize;
    int frameCount;
    float speed;
};

struct TankData {
    float moveSpeed;
    int health;
    sf::Vector2f scale;

    AnimConfig idle;
    AnimConfig walk;
    AnimConfig attack;
    AnimConfig guard;
};