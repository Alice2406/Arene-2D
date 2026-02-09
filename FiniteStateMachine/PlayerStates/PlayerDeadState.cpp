#include "PlayerDeadState.h"
#include "Player.h"
#include <iostream>

void PlayerDeadState::Enter(PlayerContext& _context)
{
	std::cout << "Enter Death state" << std::endl;
	getPlayer(_context)->setAnimation(getPlayer(_context)->textureDeath, 512, 64, 8, 0.15f, false, 0);
	getPlayer(_context)->hurtbox.isActive = false;
	getPlayer(_context)->hitbox.isActive = false;
	getPlayer(_context)->hitbox2.isActive = false;
}

void PlayerDeadState::Exit(PlayerContext& _context) {}

void PlayerDeadState::Execute(PlayerContext& _context)
{
    Player* p = getPlayer(_context);

    if (p->getCurrentFrame() >= p->getFrameCount() - 1)
    {
        p->sprite.setColor(sf::Color::Transparent);
    }
}
