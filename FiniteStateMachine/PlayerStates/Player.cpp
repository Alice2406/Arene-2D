#include "Player.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include <iostream>

Player::Player() : frameWidth(0), frameHeight(0), frameCount(0), 
currentFrame(0), animationTimer(0.f), animationSpeed(0.1f), isLooping(true), speed(200.0f),
sprite(textureIdle), 
hurtbox({ 35.f, 50.f }, { 0.f, 10.f }), hitbox({ 0.f, 0.f }, { 0.f, 0.f }),
hitbox2({ 0.f, 0.f }, { 0.f, 0.f }) {

	context.player = this;

	hurtbox.owner = this;
	hitbox.owner = this;
	hitbox2.owner = this;

	hitbox.isActive = false;
	hitbox2.isActive = false;

	sprite.setPosition({ 400, 300 });

	if (!textureIdle.loadFromFile("../Assets/Player/Warrior_Idle.png")) {
		std::cerr << "Erreur : Impossible de charger Warrior_Idle.png" << std::endl;
	}
	if (!textureRun.loadFromFile("../Assets/Player/Warrior_Run.png")) {
		std::cerr << "Erreur : Impossible de charger Warrior_Run.png" << std::endl;
	}
	if (!textureAttack.loadFromFile("../Assets/Player/Warrior_Attack1.png")) {
		std::cerr << "Erreur : Impossible de charger Warrior_Attack1.png" << std::endl;
	}

	sprite.setTexture(textureIdle);

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
	return sprite.getPosition();
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

	if (context.moveInputX < 0) {
		sprite.setScale({ -1.f, 1.f });
	}
	else if (context.moveInputX > 0) {
		sprite.setScale({ 1.f, 1.f });
	}

	fsm.Update(context);

	if (frameCount > 0) {
		animationTimer += _dt;
		if (animationTimer >= animationSpeed) {
			animationTimer = 0.f;
			currentFrame++;

			if (currentFrame >= frameCount) {
				currentFrame = isLooping ? 0 : frameCount - 1;
			}

			currentRect.position.x = currentFrame * frameWidth;
			sprite.setTextureRect(currentRect);
		}
	}

	hurtbox.Update(getPosition(), sprite.getScale().x);
	hitbox.Update(getPosition(), sprite.getScale().x);
	hitbox2.Update(getPosition(), sprite.getScale().x);
}

void Player::setAnimation(const sf::Texture& tex, int w, int h, int count, float speed, bool loop, int row)
{
	sprite.setTexture(tex);

	frameWidth = w / count;
	frameHeight = h;
	frameCount = count;
	animationSpeed = speed;
	isLooping = loop;

	currentFrame = 0;
	animationTimer = 0.f;

	currentRect.size = { frameWidth, frameHeight };
	currentRect.position = { 0, row * h };
	sprite.setTextureRect(currentRect);

	sprite.setOrigin({ frameWidth / 2.f, h / 2.f });
}
