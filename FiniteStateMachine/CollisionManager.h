#pragma once
#include "CollisionBox.h"
#include <vector>

class CollisionManager
{
private :
	std::vector<CollisionBox*> hurtboxes;
	std::vector<CollisionBox*> hitboxes;

public:
	void addHurtbox(CollisionBox* _box);
	void addHitbox(CollisionBox* _box);
	void checkCollisions();

};

