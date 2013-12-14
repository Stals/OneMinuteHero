#include "Entity.h"

Entity::Entity(bool walkable):walkable(walkable){
	CCSprite::init();
	autorelease();
}

bool Entity::isWalkable()
{
	return walkable;
}
