#include <iostream>
#include "PlayerIdleState.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

void PlayerIdleState::Enter(PlayerContext& _context)
{
	getPlayer(_context)->setAnimation(getPlayer(_context)->textureIdle, 1536, 192, 8, 0.15f, true, 0);
}

void PlayerIdleState::Exit(PlayerContext& _context)
{
}

void PlayerIdleState::Execute(PlayerContext& _context) {}
