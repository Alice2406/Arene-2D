#include <iostream>
#include "PlayerMoveState.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

void PlayerMoveState::Enter(PlayerContext _context)
{
	std::cout << "Player enter Move state" << std::endl;
	getPlayer(_context)->setAnimation(getPlayer(_context)->textureRun, 1152, 192, 6, 0.15f, true, 0);
}

void PlayerMoveState::Exit(PlayerContext _context)
{
	std::cout << "Player exit Move state" << std::endl;
}

void PlayerMoveState::Execute(PlayerContext _context)
{
	applyMouvement(_context, _context.moveInputX, _context.moveInputY, 200.0f);
}
