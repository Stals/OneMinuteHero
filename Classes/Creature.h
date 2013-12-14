#pragma once
#include "Constants.h"

// Added HP/Stats and HP bar sprite
class Creature : public CCSprite{
public:
	Creature(int maxHp, int damage);
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

private:
	int tileX;
	int tileY;

	int hp;
	int maxHp;
	int damage;
};

