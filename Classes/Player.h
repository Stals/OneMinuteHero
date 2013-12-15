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

	float getTimeSkillDelay();
	float getHealSkillDelay();
	float getFireSkillDelay();

	long long getScore();

	void shceduleRegen();

	void cleanLabels();

private:
	int exp;
	int maxExp;
	long long score;

	void showAddExpLabel(int exp);
	void showLevelupLabel();

	void regen(float dt);
};
