#include <iostream>
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "PlayerAttackState.h"

void PlayerAttackState::Enter(PlayerContext& _context)
{
	timer = 0.f;
	getPlayer(_context)->setAnimation(getPlayer(_context)->textureAttack, 768, 192, 4, 0.15f, true, 0);

	getPlayer(_context)->hitbox.ResetHit();
	getPlayer(_context)->hitbox2.ResetHit();
}

void PlayerAttackState::Exit(PlayerContext& _context)
{
	getPlayer(_context)->hitbox.isActive = false;
	getPlayer(_context)->hitbox2.isActive = false;

	getPlayer(_context)->hitbox.ResetHit();
	getPlayer(_context)->hitbox2.ResetHit();
}

void PlayerAttackState::Execute(PlayerContext& _context)
{
	timer += _context.deltaTime;
	Player* p = getPlayer(_context);

	if (timer >= 0.30f && timer < 0.60f)
	{
		p->hitbox.isActive = true;
		p->hitbox2.isActive = true;
	}
	else
	{
		p->hitbox.isActive = false;
		p->hitbox2.isActive = false;
	}

	if (hasMouvementInput(_context)) {
		applyMouvement(_context, _context.moveInputX, _context.moveInputY, 300.0f);
	}
}