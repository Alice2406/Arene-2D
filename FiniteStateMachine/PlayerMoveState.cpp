#include <iostream>
#include "PlayerMoveState.h"

void PlayerMoveState::Enter(PlayerContext _context)
{
	std::cout << "Enter Move State" << std::endl;
}

void PlayerMoveState::Exit(PlayerContext _context)
{
	std::cout << "Exit Move State" << std::endl;
}

void PlayerMoveState::Execute(PlayerContext _context)
{
	ApplyMouvement(_context, _context.moveInputX, _context.moveInputY, 200.0f);
}
