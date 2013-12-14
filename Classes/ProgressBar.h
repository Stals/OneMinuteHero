#pragma once

#include "Constants.h"

class ProgressBar : public CCSprite{
public:
	ProgressBar(CCSprite* emptyBar, CCSprite* fullBar);
	ProgressBar(const char* emptyBarFileName, const char* fullBarFileName);
};

