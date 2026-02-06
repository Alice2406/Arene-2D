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
    sf::Texture& GetTexture(const std::string& path)
    {
        if (m_textures.find(path) == m_textures.end())
        {
            sf::Texture& tex = m_textures[path];
            if (!tex.loadFromFile(path))
            {
                std::cout << "error path" << path << std::endl;
            }
            return tex;
        }
        return m_textures[path];
    }
};