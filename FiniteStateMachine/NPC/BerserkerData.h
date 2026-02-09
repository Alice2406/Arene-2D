#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>

enum class BerserkerSkin {
    BEAR,
    GNOME,
    LANCER,
    PADDLEFISH,
    THIEF,
    TROLL
};
struct AnimConfig {
    std::string texturePath;
    sf::Vector2i frameSize;
    int frameCount;
    float speed;
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