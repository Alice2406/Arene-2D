#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

class ResourceManager
{
private:
    std::map<std::string, sf::Texture> m_textures;

public:
    sf::Texture& GetTexture(const std::string& path);
};