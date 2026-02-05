#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "PlayerAttackState.h"

void PlayerAttackState::Enter(PlayerContext _context)
{
	timer = 0.f;
	std::cout << "Player enter Attack state" << std::endl;
	GetPlayer(_context)->setAnimation(GetPlayer(_context)->textureAttack, 768, 192, 4, 0.15f, true, 0);
}

void PlayerAttackState::Exit(PlayerContext _context)
{
	std::cout << "Player exit Attack state" << std::endl;
}

void PlayerAttackState::Execute(PlayerContext _context)
{
	timer += _context.deltaTime;

	if (HasMouvementInput(_context)) {
		ApplyMouvement(_context, _context.moveInputX, _context.moveInputY, 200.0f);
	}
}
