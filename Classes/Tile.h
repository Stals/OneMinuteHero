#pragma once
#include "Constants.h"


class BoardTile : public cocos2d::CCSprite{
public:
	BoardTile(bool walkable);

	bool isWalkable();

private:
	bool walkable;

};
