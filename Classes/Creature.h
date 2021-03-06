#pragma once
#include "Constants.h"
#include "ProgressBar.h"

// Added HP/Stats and HP bar sprite
class Creature : public CCSprite{
public:
	Creature(const char* fileName, int maxHp, int damage, int level);
	void setTileX(int x);
	void setTileY(int y);
	void setTilePosition(int x, int y);

	int getTileX();
	int getTileY();

	// �������� �� �� ���� + �����
	void substractHp(int hp, bool animated = true);
	void addHp(int hp, bool animated = true);

	int getHP();
	int getMaxHP();

	int getDamage();
	int getLevel();

	bool isDead();

protected:
	int tileX;
	int tileY;

	int level;

	int hp;
	int maxHp;
	int damage;

	//ProgressBar* hpBar;

	void setupHPBar();

	// scales var depending on the level
	int scaleVar(int var);
};

