#include "ProgressBar.h"	

ProgressBar::ProgressBar(CCSprite* emptyBar, CCSprite* fullBar)
{
	CCSprite::init();
	//setContentSize(emptyBar->getContentSize());
	//this->setAnchorPoint(ccp(0,0.5));
	
	
	this->addChild(emptyBar);
	//this->addChild(fullBar);
	emptyBar->setAnchorPoint(ccp(0.5,0.5));
	fullBar->setAnchorPoint(ccp(0.5,0.5));


	autorelease();
	
	fuelBar = CCProgressTimer::create(fullBar);
	fuelBar->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
	fuelBar->setAnchorPoint(ccp(0.5,0.5));
	fuelBar->setBarChangeRate(ccp(1,0));
	fuelBar->setTag(1);                 

	this->addChild(fuelBar);
	fuelBar->setPercentage(100); // Value between 0-100
}

void ProgressBar::setPercent(float percent)
{
	fuelBar->setPercentage(percent);
}


ProgressBar::ProgressBar(const char* emptyBarFileName, const char* fullBarFileName)
{
	//ProgressBar(CCSprite::create(emptyBarFileName), CCSprite::create(fullBarFileName));
}