#pragma once
#include "Scene.h"
#include "../Animation-Assets/ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <vector> 

class MenuScene : public Scene
{
private:
    ResourceManager& m_resources;
    sf::Font m_font;

    sf::Sprite m_background;

    sf::Sprite m_ribbonSprite;
    sf::Text m_titleText;

    sf::Sprite m_btnPlay;
    sf::Text   m_textPlay;
    sf::Sprite m_btnQuit;
    sf::Text   m_textQuit;

    void BuildRibbonGiant(sf::Vector2u windowSize); 
    void InitButton(sf::Sprite& sprite, sf::Text& text, std::string str, float x, float y);
    void UpdateButtonState(sf::Sprite& sprite, sf::Text& text, sf::Vector2f mousePos);

public:
    MenuScene(sf::Vector2u windowSize, ResourceManager& resources);
    virtual SceneType Update(float dt, sf::RenderWindow& window) override;
    virtual void Draw(sf::RenderWindow& window) override;
};;