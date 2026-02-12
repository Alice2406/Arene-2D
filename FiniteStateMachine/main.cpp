#include <SFML/Graphics.hpp>
#include <memory>
#include "Scene/MenuScene.h"
#include "Scene/GameScene.h"
#include "Animation-Assets/ResourceManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "Arene 2D");
    window.setFramerateLimit(60);
    srand(static_cast<unsigned int>(time(NULL)));
    ResourceManager resourceManager;
    resourceManager.LoadAllGameTextures();
    std::unique_ptr<Scene> currentScene = std::make_unique<MenuScene>(window.getSize(), resourceManager);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        SceneType request = currentScene->Update(dt, window);

        if (request != SceneType::None)
        {
            if (request == SceneType::Game)
            {
                currentScene = std::make_unique<GameScene>(window, resourceManager);
            }
            else if (request == SceneType::Menu)
            {
                currentScene = std::make_unique<MenuScene>(window.getSize(), resourceManager);
            }
        }

        window.clear();
        currentScene->Draw(window);
        window.display();
    }

    return 0;
}