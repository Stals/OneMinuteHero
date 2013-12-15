#pragma once

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace cocos2d;

enum zOrder{
	zBackground,
	zBoard,
	zAOE,
	zCreature,
	zWall,
	zTutorial,
	zGameover
};

enum SkillType{
	Fire,
	Heal,
	Time
};
