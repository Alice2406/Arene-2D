#include "MenuScene.h"
#include "../Animation-Assets/AssetPath.h"
#include <iostream>

MenuScene::MenuScene(sf::Vector2u windowSize, ResourceManager& resources)
    : m_resources(resources),
    m_font(),
    m_titleText(m_font),
    m_textPlay(m_font),
    m_textQuit(m_font),
    m_ribbonSprite(resources.GetTexture("MenuTitle")),
    m_background(resources.GetTexture("MenuBackground")),
    m_btnPlay(resources.GetTexture("BtnPlay")), 
    m_btnQuit(resources.GetTexture("BtnQuit"))
{
    if (!m_font.openFromFile(AssetPaths::UI::MAIN_FONT)) {
        std::cerr << "ERREUR CRITIQUE : Impossible de charger la police !" << std::endl;
    }

    sf::Vector2u bgSize = m_background.getTexture().getSize();
    m_background.setScale({
        (float)windowSize.x / bgSize.x,
        (float)windowSize.y / bgSize.y
        });

    BuildRibbonGiant(windowSize);

    float centerX = windowSize.x / 2.0f;

    InitButton(m_btnPlay, m_textPlay, "Jouer", centerX, 450.f);

    InitButton(m_btnQuit, m_textQuit, "Quitter", centerX, 650.f);
}

void MenuScene::BuildRibbonGiant(sf::Vector2u windowSize)
{
    auto texSize = m_ribbonSprite.getTexture().getSize();
    m_ribbonSprite.setTextureRect(sf::IntRect({ 0, 0 }, { (int)texSize.x, (int)texSize.y }));

    float scaleFactor = 2.0f;
    m_ribbonSprite.setScale({ scaleFactor, scaleFactor });

    sf::FloatRect bounds = m_ribbonSprite.getGlobalBounds();
    m_ribbonSprite.setPosition({ (windowSize.x - bounds.size.x) / 2.f, 50.f });

    m_titleText.setString("Arene Survivor");
    m_titleText.setCharacterSize(static_cast<unsigned int>(30 * scaleFactor));
    m_titleText.setFillColor(sf::Color::White);
    //m_titleText.setOutlineColor(sf::Color::Black);
    //m_titleText.setOutlineThickness(2.f * scaleFactor);

    sf::FloatRect tBounds = m_titleText.getLocalBounds();

    m_titleText.setOrigin({
        tBounds.position.x + tBounds.size.x / 2.f,
        tBounds.position.y + tBounds.size.y / 2.f
        });

    float decalageTexteX = 500.0f;

    float decalageTexteY = 50.0f;

    m_titleText.setPosition({
        bounds.position.x + (bounds.size.x / 2.f) + decalageTexteX,
        bounds.position.y + (bounds.size.y / 2.f) + decalageTexteY
        });
}

void MenuScene::InitButton(sf::Sprite& sprite, sf::Text& text, std::string str, float x, float y)
{
    sf::FloatRect sBounds = sprite.getLocalBounds();
    sprite.setOrigin({ sBounds.size.x / 2.f, sBounds.size.y / 2.f });
    sprite.setPosition({ x, y });
    sprite.setScale({ 1.f, 1.f });

    text.setString(str);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color(50, 50, 50)); 

    sf::FloatRect tBounds = text.getLocalBounds();
    text.setOrigin({ tBounds.position.x + tBounds.size.x / 2, tBounds.position.y + tBounds.size.y / 2 });
    text.setPosition({ x, y - 5.f }); 
}

void MenuScene::UpdateButtonState(sf::Sprite& sprite, sf::Text& text, sf::Vector2f mousePos)
{
    bool isHover = sprite.getGlobalBounds().contains(mousePos);

    if (isHover)
    {
        sprite.setColor(sf::Color(230, 230, 230)); 
        sprite.setScale({ 1.1f, 1.1f });             
        text.setFillColor(sf::Color::Black);       
        text.setScale({ 1.1f, 1.1f });               
    }
    else
    {
        sprite.setColor(sf::Color::White);
        sprite.setScale({ 1.f, 1.f });
        text.setFillColor(sf::Color(50, 50, 50));
        text.setScale({ 1.0f, 1.0f });
    }
}

SceneType MenuScene::Update(float dt, sf::RenderWindow& window)
{
    sf::Vector2i pixel = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(pixel);

    UpdateButtonState(m_btnPlay, m_textPlay, mouse);
    UpdateButtonState(m_btnQuit, m_textQuit, mouse);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (m_btnPlay.getGlobalBounds().contains(mouse)) {
            return SceneType::Game;
        }
        if (m_btnQuit.getGlobalBounds().contains(mouse)) {
            window.close();
        }
    }

    return SceneType::None;
}

void MenuScene::Draw(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());

    window.draw(m_background);


    window.draw(m_ribbonSprite);
    window.draw(m_titleText);

    window.draw(m_btnPlay);
    window.draw(m_btnQuit);

    window.draw(m_textPlay);
    window.draw(m_textQuit);
}