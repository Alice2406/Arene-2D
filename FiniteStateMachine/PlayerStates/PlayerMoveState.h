#pragma once
#include "PlayerBaseState.h"

class PlayerMoveState : public PlayerBaseState
{
public:
	void Enter(PlayerContext _context) override;
	void Exit(PlayerContext _context) override;
	void Execute(PlayerContext _context) override;
};

