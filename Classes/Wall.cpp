#include "Wall.h"

Wall::Wall():BoardTile(false){
	CCSprite* sprite = CCSprite::create("wall.png");
	sprite->setOpacity(200);
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
}
