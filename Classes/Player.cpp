#include "Player.h"

Player::Player(int maxHp, int damage):Creature(maxHp, damage)
{
	CCSprite* sprite = CCSprite::create("hero.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}
