#include "Player.h"
#include "SFML/Graphics.hpp"

sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}

void Player::Update(sf::RenderWindow& window)
{
	sf::Vector2f movement(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		movement.y += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		movement.y -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		movement.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		movement.x += 1;

	shape.move(movement * speed);
}
