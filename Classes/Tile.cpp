#include "Tile.h"

BoardTile::BoardTile(bool walkable):walkable(walkable){
	CCSprite::init();
	autorelease();
}

bool BoardTile::isWalkable()
{
	return walkable;
}
