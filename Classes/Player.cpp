#include "Player.h"

Player::Player(int maxHp):Creature(maxHp)
{
	CCSprite* sprite = CCSprite::create("hero.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}
