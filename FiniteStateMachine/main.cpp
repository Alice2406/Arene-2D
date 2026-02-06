#include "NPC/Berserker.h"
#include "NPC/Sniper.h"
#include "NPC/Tank.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1900, 800 }), "SFML works!");
    window.setFramerateLimit(60);
    srand(time(NULL));

    sf::Clock clock;
    Player player;

    std::vector<Tank*> tanks;

    Tank* t1 = new Tank(TankSkin::TURTLE);
    t1->Init(); 
    t1->setPosition({ -10.f, -10.f });
    tanks.push_back(t1);

    // Tu peux en ajouter un deuxième facilement maintenant :
    // Tank* t2 = new Tank(TankSkin::FISH);
    // t2->Init();
    // tanks.push_back(t2);
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

        for (Tank* t : tanks)
        {
            t->context.deltaTime = dt;
            t->context.playerPos = player.getPosition();

            t->Update(dt);
        }
        window.draw(player.getShape());

        for (Tank* t : tanks)
        {
            window.draw(t->getSprite()); 
        }

        window.display();
    }
    for (Tank* t : tanks) delete t;

    return 0;
}
