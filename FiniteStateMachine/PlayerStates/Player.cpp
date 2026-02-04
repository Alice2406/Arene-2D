#include "Player.h"
#include "PlayerMoveState.h"

Player::Player() : shape({ 30.f, 30.f }), speed(5.f) {
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition({ 50.f, 50.f });
}

sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}

void Player::Update(sf::RenderWindow& window, float _dt)
{
	context.player = this;

	context.deltaTime = _dt;
	context.moveInputX = 0;
	context.moveInputY = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		context.moveInputY += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		context.moveInputY -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		context.moveInputX -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		context.moveInputX += 1;

	fsm.Update(context);
}
