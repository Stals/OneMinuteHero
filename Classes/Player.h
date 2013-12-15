#pragma once

#include "Creature.h"

class Player : public Creature{
public:
	Player(int maxHp, int damage);

	void addExp(int exp);

	int getExp();
	int getMaxExp();

	int getHealAmount();
	int getFireDamage();
	int getStopTimeSeconds();

	long long getScore();

private:
	int exp;
	int maxExp;
	long long score;

	void showAddExpLabel(int exp);
	void showLevelupLabel();
};
