#include "Player.h"
#include "NPC/EnemyManager.h" 
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "SFML works!");
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Clock clock;
    Player player;

    EnemyManager enemyManager;

    enemyManager.SpawnTank(TankSkin::TURTLE, { -10.f, -10.f });
    enemyManager.SpawnTank(TankSkin::PANDA, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::THIEF, { -10.f, -10.f });
    enemyManager.SpawnBerserker(BerserkerSkin::LANCER, { -10.f, -10.f });
    enemyManager.SpawnSniper(SniperSkin::GNOLL, { -10.f, -10.f });
    enemyManager.SpawnSniper(SniperSkin::SHAMAN, { -10.f, -10.f });

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        player.Update(window);
        enemyManager.Update(dt, player.getPosition());
        window.draw(player.getShape());
        enemyManager.Draw(window);

        window.display();
    }

    return 0;
}