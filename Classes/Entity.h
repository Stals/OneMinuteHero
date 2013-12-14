#pragma once
#include "Constants.h"

class Entity : public cocos2d::CCSprite{
public:
	Entity(bool walkable);

	bool isWalkable();

private:
	bool walkable;

};
