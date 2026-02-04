#pragma once
#include "../StateMachine/State.h"
#include "PlayerContext.h"

class Player;

class PlayerBaseState : public FSM::State<PlayerContext>
{
protected:
	Player* GetPlayer(PlayerContext& _context) const;
	bool HasMouvementInput(const PlayerContext& _context) const;
	void ApplyMouvement(PlayerContext& _context, float _inputX, float _inputY, float _speed) const;

public:
	virtual ~PlayerBaseState() = default;
};

