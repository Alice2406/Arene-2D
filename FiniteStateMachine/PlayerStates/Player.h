#pragma once
#include "PlayerContext.h"
#include "../StateMachine/StateMachine.h"
#include "SFML/Graphics.hpp"

class Player
{
private:
	sf::RectangleShape shape; //sa forme
	float speed; //sa vitesse
	sf::Vector2f velocity; //mouvement
public:
	Player();

	sf::Vector2f getPosition();
	void Update(sf::RenderWindow& window, float _dt);
	sf::RectangleShape& getShape() { return shape; }

	PlayerContext context;
	FSM::StateMachine<PlayerContext> fsm;
};


