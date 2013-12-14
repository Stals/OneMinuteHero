#include "Entity.h"

Entity::Entity(bool walkable):walkable(walkable){
	CCSprite::init();
}

bool Entity::isWalkable()
{
	return walkable;
}
