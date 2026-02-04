#include "Player.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"

Player::Player() : shape({ 30.f, 30.f }), speed(5.f) {
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition({ 50.f, 50.f });

	context.player = this;

	PlayerIdleState* idle = fsm.CreateState<PlayerIdleState>();
	PlayerMoveState* move = fsm.CreateState<PlayerMoveState>();

	idle->AddTransition([this](PlayerContext _c) {
		return (_c.moveInputX != 0 || _c.moveInputY != 0);
		}, move);

	move->AddTransition([this](PlayerContext _c) {
		return (_c.moveInputX == 0 && _c.moveInputY == 0);
		}, idle);

	fsm.Init(idle, context);
}

sf::Vector2f Player::getPosition()
{
	return shape.getPosition();
}

void Player::Update(sf::RenderWindow& window, float _dt)
{
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
