#pragma once

class Player;

class PlayerContext
{
public:
	Player* player;

	float moveInputX;
	float moveInputY;
	bool isAttackPressed;

	float deltaTime;
};
