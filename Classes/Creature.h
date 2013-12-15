#pragma once
#include "Constants.h"
#include "ProgressBar.h"

// Added HP/Stats and HP bar sprite
class Creature : public CCSprite{
public:
	Creature(const char* fileName, int maxHp, int damage);
	void setTileX(int x);
	void setTileY(int y);
	void setTilePosition(int x, int y);

	int getTileX();
	int getTileY();

	// анимация на хп баре + текст
	void substractHp(int hp, bool animated = true);
	void addHp(int hp, bool animated = true);
	int getDamage();

	bool isDead();

protected:
	int tileX;
	int tileY;

	int hp;
	int maxHp;
	int damage;

	//ProgressBar* hpBar;

	void setupHPBar();
};

