#pragma once
#include <string>
#include <SFML/System.hpp>

struct AnimConfig {
    std::string texturePath;
    sf::Vector2i frameSize;
    int frameCount;
    float speed;
};