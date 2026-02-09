#pragma once
#include "../StateMachine/State.h"
#include "PlayerContext.h"

class Player;

class PlayerBaseState : public FSM::State<PlayerContext>
{
protected:
	Player* getPlayer(PlayerContext& _context) const;
	bool hasMouvementInput(const PlayerContext& _context) const;
	void applyMouvement(PlayerContext& _context, float _inputX, float _inputY, float _speed) const;

public:
	virtual ~PlayerBaseState() = default;
};

