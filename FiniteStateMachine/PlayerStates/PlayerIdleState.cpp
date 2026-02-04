#include <iostream>
#include "PlayerIdleState.h"
#include "Player.h"
#include "SFML/Graphics.hpp"

void PlayerIdleState::Enter(PlayerContext _context)
{
	std::cout << " Player enter Idle state" << std::endl;
	Player* p = GetPlayer(_context);
	if (p) {
		p->getShape().setFillColor(sf::Color::Blue);
	}
}

void PlayerIdleState::Exit(PlayerContext _context)
{
	std::cout << " Player exit Idle state" << std::endl;
}

void PlayerIdleState::Execute(PlayerContext _context) {}
