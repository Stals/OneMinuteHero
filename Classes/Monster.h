#pragma once

#include "Creature.h"

class Monster : public Creature{
public:
	Monster(int maxHp, int damage, int level);

	int getRewardExp();
};
