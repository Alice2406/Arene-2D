#include "Player.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"

Player::Player() : shape({ 30.f, 30.f }), speed(5.f) {
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition({ 50.f, 50.f });

	context.player = this;

	PlayerIdleState* idle = fsm.CreateState<PlayerIdleState>();
	PlayerMoveState* move = fsm.CreateState<PlayerMoveState>();
	PlayerAttackState* attack = fsm.CreateState<PlayerAttackState>();

	idle->AddTransition([this](PlayerContext _c) { return (_c.moveInputX != 0 || _c.moveInputY != 0); }, move);
	idle->AddTransition([](PlayerContext _c) { return _c.isAttackPressed; }, attack);

	move->AddTransition([this](PlayerContext _c) { return (_c.moveInputX == 0 && _c.moveInputY == 0); }, idle);
	move->AddTransition([](PlayerContext _c) { return _c.isAttackPressed; }, attack);

	attack->AddTransition([attack](PlayerContext _c) { return attack->IsFinished() && (_c.moveInputX == 0 && _c.moveInputY == 0); }, idle);
	attack->AddTransition([attack](PlayerContext _c) { return attack->IsFinished() && (_c.moveInputX != 0 || _c.moveInputY != 0); }, move);

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
	context.isAttackPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		context.moveInputY += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		context.moveInputY -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		context.moveInputX -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		context.moveInputX += 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		context.isAttackPressed = true;

	fsm.Update(context);
}
