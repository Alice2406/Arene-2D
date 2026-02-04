#pragma once
#include "PlayerStates/PlayerBaseState.h"

class PlayerMoveState : public PlayerBaseState
{
public:
	void Execute(PlayerContext _context) override;
};

