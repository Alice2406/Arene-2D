#include <iostream>
#include "PlayerMoveState.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

void PlayerMoveState::Enter(PlayerContext _context)
{
	std::cout << "Player enter Move state" << std::endl;
	Player* p = GetPlayer(_context);
	if (p) {
		p->getShape().setFillColor(sf::Color::Green);
	}
}

void PlayerMoveState::Exit(PlayerContext _context)
{
	std::cout << "Player exit Move state" << std::endl;
}

void PlayerMoveState::Execute(PlayerContext _context)
{
	ApplyMouvement(_context, _context.moveInputX, _context.moveInputY, 200.0f);
}
