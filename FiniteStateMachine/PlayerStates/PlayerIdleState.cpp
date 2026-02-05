#include <iostream>
#include "PlayerIdleState.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

void PlayerIdleState::Enter(PlayerContext _context)
{
	std::cout << " Player enter Idle state" << std::endl;
	GetPlayer(_context)->setAnimation(GetPlayer(_context)->textureIdle, 1536, 192, 8, 0.15f, true, 0);
}

void PlayerIdleState::Exit(PlayerContext _context)
{
	std::cout << " Player exit Idle state" << std::endl;
}

void PlayerIdleState::Execute(PlayerContext _context) {}
