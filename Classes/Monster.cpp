#include "Monster.h"

Monster::Monster(int maxHp, int damage): Creature(maxHp, damage){
	CCSprite* sprite = CCSprite::create("monster.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
	autorelease();
}
