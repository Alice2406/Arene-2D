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
    void LoadTexture(const std::string& name, const std::string& path);
    sf::Texture& GetTexture(const std::string& path);
    void LoadAllGameTextures();
};