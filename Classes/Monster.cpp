#include "Monster.h"

Monster::Monster(int maxHp): Creature(maxHp){
	CCSprite* sprite = CCSprite::create("monster.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}
