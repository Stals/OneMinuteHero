#pragma once

#include "Constants.h"


class TutorialLayer : public CCLayer{
public:
	TutorialLayer();
	~TutorialLayer();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

private:
	void setupBackground();
};

