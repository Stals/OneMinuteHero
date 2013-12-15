#pragma once

#include "Constants.h"
#include "Timer.h"


class TutorialLayer : public CCLayer{
public:
	TutorialLayer(TimerSprite* timer);
	~TutorialLayer();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

private:
	TimerSprite* timer;
	void setupBackground();
};

