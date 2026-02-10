#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray m_vertices;
    const sf::Texture* m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        states.texture = m_tileset;
        target.draw(m_vertices, states);
    }

    void generateVertices(sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width, unsigned int height)
    {
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];

                int tu = tileNumber % (m_tileset->getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset->getSize().x / tileSize.x);

                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }
    }

public:
    bool load(const std::string& levelPath, const std::string& tilesetPath, sf::Vector2u tileSize)
    {
        static sf::Texture tileset;
        if (!tileset.loadFromFile(tilesetPath)) {
            std::cout << "Erreur : Texture introuvable " << tilesetPath << std::endl;
            return false;
        }
        m_tileset = &tileset;

        std::ifstream file(levelPath);
        if (!file.is_open()) {
            std::cout << "Erreur : Fichier niveau introuvable " << levelPath << std::endl;
            return false;
        }

        std::vector<int> tiles;
        std::string line;
        unsigned int width = 0;
        unsigned int height = 0;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string cell;
            int currentWidth = 0;

            while (std::getline(ss, cell, ','))
            {
                if (!cell.empty()) {
                    tiles.push_back(std::stoi(cell));
                    currentWidth++;
                }
            }

            if (width == 0) width = currentWidth;
            height++;
        }

        file.close();

        if (width > 0 && height > 0) {
            generateVertices(tileSize, tiles, width, height);
            return true;
        }

        return false;
    }
};