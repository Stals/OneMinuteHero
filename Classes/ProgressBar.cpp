#include "ProgressBar.h"	

ProgressBar::ProgressBar(CCSprite* emptyBar, CCSprite* fullBar)
{
	CCSprite::init();
	setContentSize(emptyBar->getContentSize());
	this->setAnchorPoint(ccp(0.5,0.5));
	
	//fullBar->setAnchorPoint(ccp(0,0.5));
	this->addChild(emptyBar);
	this->addChild(fullBar);

	fullBar->setScaleX(0.7);

	autorelease();
}


ProgressBar::ProgressBar(const char* emptyBarFileName, const char* fullBarFileName)
{
	//ProgressBar(CCSprite::create(emptyBarFileName), CCSprite::create(fullBarFileName));
}