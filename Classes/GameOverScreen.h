#pragma once

#include "Constants.h"

class GameOverScreen : public CCLayer{
public:
	~GameOverScreen();
	virtual bool init();
	static cocos2d::CCScene* scene();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

private:
	CREATE_FUNC(GameOverScreen);

	void setupBackground();
};

