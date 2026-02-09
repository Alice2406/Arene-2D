#pragma once
#include "PlayerBaseState.h"

class PlayerAttackState : public PlayerBaseState 
{
private:
	float timer = 0.f;
	float duration = 0.6f;

public:
	void Enter(PlayerContext& _context) override;
	void Exit(PlayerContext& _context) override;
	void Execute(PlayerContext& _context) override;
	
	bool IsFinished() const { return timer >= duration; }
};