#include "Monster.h"
#include "StringExtension.h"

Monster::Monster(int maxHp, int damage, int level): 
Creature((std::string("monster") + StringExtension::toString(rand()%5 +1) + ".png").c_str(), maxHp, damage, level){
	/*CCSprite* sprite = CCSprite::create("monster.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);*/
	autorelease();
}

int Monster::getRewardExp()
{
	return scaleVar(10);
}
