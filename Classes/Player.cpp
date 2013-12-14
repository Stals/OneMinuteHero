#include "Player.h"

Player::Player(int hp, int maxHp):Creature(hp, maxHp)
{
	CCSprite* sprite = CCSprite::create("hero.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}
