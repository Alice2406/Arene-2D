#include "ResourceManager.h"
#include "../Animation-Assets/AssetPath.h" // <--- TRES IMPORTANT

void ResourceManager::LoadTexture(const std::string& name, const std::string& path)
{
    sf::Texture tex;
    if (tex.loadFromFile(path))
    {
        m_textures[name] = tex; 
    }
    else
    {
        std::cerr << "ERREUR: Impossible de charger " << path << std::endl;
    }
}

void ResourceManager::LoadAllGameTextures()
{
    // 1. Map
    LoadTexture("Water", AssetPaths::Environment::TILESET_WATER);
    LoadTexture("MapTiles", AssetPaths::Environment::TILESET_GROUND);

    // 2. Obstacles Solides
    LoadTexture("Rock1", AssetPaths::Environment::ROCK1);
    LoadTexture("Rock2", AssetPaths::Environment::ROCK2);
    LoadTexture("Rock3", AssetPaths::Environment::ROCK3);
    LoadTexture("Rock4", AssetPaths::Environment::ROCK4);
    LoadTexture("Tree", AssetPaths::Environment::TREE);

    // 3. Animaux
    LoadTexture("Sheep1", AssetPaths::Animals::SHEEP_WHITE);
    LoadTexture("Sheep2", AssetPaths::Animals::SHEEP_BLACK);

    // 4. Décorations
    LoadTexture("Bush1", AssetPaths::Environment::BUSH1);
    LoadTexture("Bush2", AssetPaths::Environment::BUSH2);
    LoadTexture("Bush3", AssetPaths::Environment::BUSH3);
}

sf::Texture& ResourceManager::GetTexture(const std::string& path)
{
    if (m_textures.find(path) == m_textures.end())
    {
        sf::Texture& tex = m_textures[path];
        if (!tex.loadFromFile(path)) {
            std::cerr << "Erreur chargement: " << path << std::endl;
        }
        return tex;
    }

    return m_textures[path];
}
