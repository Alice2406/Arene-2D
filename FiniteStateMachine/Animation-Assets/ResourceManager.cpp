#include "ResourceManager.h"

sf::Texture& ResourceManager::GetTexture(const std::string& path)
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
