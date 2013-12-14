#include "Creature.h"

Creature::Creature(int hp, int maxHp): tileX(0), tileY(0), hp(hp), maxHp(maxHp)
{
	CCSprite::init();
	autorelease();
}

void Creature::setTileX(int x)
{
	tileX = x;
}

void Creature::setTileY(int y)
{
	tileY = y;
}

void Creature::setTilePosition(int x, int y)
{
	tileX = x;
	tileY = y;
}

int Creature::getTileX()
{
	return tileX;
}

int Creature::getTileY()
{
	return tileY;
}