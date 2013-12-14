#include "Stairs.h"

Stairs::Stairs():BoardTile(true)
{
	CCSprite* sprite = CCSprite::create("stairs.png");
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}