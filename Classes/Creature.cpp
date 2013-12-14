#include "Creature.h"

Creature::Creature(int hp, int maxHp): hp(hp), maxHp(maxHp)
{
	CCSprite::init();
	autorelease();
}

