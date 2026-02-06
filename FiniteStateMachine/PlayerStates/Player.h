#pragma once
#include "PlayerContext.h"
#include "../CollisionBox.h"
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"

class Player
{
private:
	sf::IntRect currentRect;
	int frameWidth, frameHeight, frameCount;
	int currentFrame = 0;
	float animationTimer = 0.0f;
	float animationSpeed;
	bool isLooping;

	float speed;
	sf::Vector2f velocity;

public:
	sf::Texture textureIdle;
	sf::Texture textureRun;
	sf::Texture textureAttack;
	sf::Sprite sprite;

	CollisionBox hurtbox;
	CollisionBox hitbox;
	CollisionBox hitbox2;
	
	Player();

	sf::Vector2f getPosition();
	void Update(sf::RenderWindow& window, float _dt);
	void setAnimation(const sf::Texture& tex, int w, int h, int count, float speed, bool loop, int row);
	sf::Sprite& getSprite() { return sprite; }

	PlayerContext context;
	FSM::StateMachine<PlayerContext> fsm;
};


