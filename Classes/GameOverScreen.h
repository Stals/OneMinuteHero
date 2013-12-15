#pragma once

#include "Constants.h"

class GameOverScreen : public CCLayer{
public:
	~GameOverScreen();
	virtual bool init();
	static cocos2d::CCScene* scene(long long score);


	void setScore(long long score);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

		void setupLabel();

private:
	long long score;

	CREATE_FUNC(GameOverScreen);

	void setupBackground();

};

