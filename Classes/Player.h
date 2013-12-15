#pragma once

#include "Creature.h"

class Player : public Creature{
public:
	Player(int maxHp, int damage);

	void addExp(int exp);

	int getExp();
	int getMaxExp();

private:
	int exp;
	int maxExp;

	void showAddExpLabel(int exp);
	void showLevelupLabel();
};
