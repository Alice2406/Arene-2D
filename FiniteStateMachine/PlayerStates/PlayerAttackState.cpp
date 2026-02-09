#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "PlayerAttackState.h"

void PlayerAttackState::Enter(PlayerContext _context)
{
	timer = 0.f;
	std::cout << "Player enter Attack state" << std::endl;
	getPlayer(_context)->setAnimation(getPlayer(_context)->textureAttack, 768, 192, 4, 0.15f, true, 0);
}

void PlayerAttackState::Exit(PlayerContext _context)
{
	std::cout << "Player exit Attack state" << std::endl;
	getPlayer(_context)->hitbox.isActive = false;
	getPlayer(_context)->hitbox2.isActive = false;
}

void PlayerAttackState::Execute(PlayerContext _context)
{
	timer += _context.deltaTime;
	Player* p = getPlayer(_context);

	if (timer >= 0.f && timer < 0.60f)
	{
		p->hitbox.isActive = true;
		p->hitbox.bounds.size = { 60.f, 90.f };
		p->hitbox.offset = { 28.f, 0.f };

		p->hitbox2.isActive = true;
		p->hitbox2.bounds.size = { 100.f, 40.f };
		p->hitbox2.offset = { 0.f, 40.f };
	}

    else
    {
        p->hitbox.isActive = false;
        p->hitbox2.isActive = false;
    }

	if (hasMouvementInput(_context)) {
		applyMouvement(_context, _context.moveInputX, _context.moveInputY, 200.0f);
	}

}
