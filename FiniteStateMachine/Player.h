#pragma once
#include "SFML/Graphics.hpp"

class Player
{
private:
	sf::RectangleShape shape; //sa forme
	float speed; //sa vitesse
	sf::Vector2f velocity; //mouvement
public:
	Player() : shape({ 30.f, 30.f }), speed(5.f) {
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition({ 50.f, 50.f });
	}
	sf::Vector2f getPosition();
	void Update(sf::RenderWindow& window);
	sf::RectangleShape& getShape() { return shape; }
};

