#include "PlayerBaseState.h"
#include "Player.h"
#include <cmath>

Player* PlayerBaseState::GetPlayer(PlayerContext& _context) const
{
    return _context.player;
}

bool PlayerBaseState::HasMouvementInput(const PlayerContext& _context) const
{
	return (_context.moveInputX != 0 || _context.moveInputY != 0);
}

void PlayerBaseState::ApplyMouvement(PlayerContext& _context, float _inputX, float _inputY, float _speed) const
{
	Player* player = GetPlayer(_context);
	if (!player) return;
	
	float magnitude = std::sqrt(_inputX * _inputX + _inputY * _inputY);
	if (magnitude > 1.f) {
		_inputX /= magnitude;
		_inputY /= magnitude;
	}

	sf::Vector2f movement(_inputX * _speed * _context.deltaTime, _inputY * _speed * _context.deltaTime);
	player->getSprite().move(movement);
}
