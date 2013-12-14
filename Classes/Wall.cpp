#include "Wall.h"

Wall::Wall():Entity(false){
	CCSprite* sprite = CCSprite::create("wall.png");
	sprite->setOpacity(127);
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);

	autorelease();
}
