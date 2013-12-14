#include "Creature.h"

Creature::Creature(int maxHp, int damage): tileX(0), tileY(0), hp(maxHp), maxHp(maxHp), damage(damage)
{
	CCSprite::init();
	//autorelease();
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


void Creature::substractHp(int hp, bool animated)
{
	this->hp -= hp;
}

void Creature::addHp(int hp, bool animated)
{
	if(this->hp + hp > this->maxHp){
		this->hp = this->maxHp;
	}else{
		this->hp += hp;
	}
}

int Creature::getDamage()
{
	return damage;
}

bool Creature::isDead(){
	return hp <= 0;
}

