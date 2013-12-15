#pragma once

#include "Constants.h"
#include "Timer.h"
#include "Keyboard.h"

class TutorialLayer : public CCLayer{
public:
	TutorialLayer(TimerSprite* timer, Keyboard** keyboard);
	~TutorialLayer();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

private:
	TimerSprite* timer;
	Keyboard** keyboard;
	void setupBackground();
};

