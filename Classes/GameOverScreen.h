#pragma once

#include "Constants.h"
#include "Keyboard.h"

class GameOverScreen : public CCLayer{
public:
	GameOverScreen(long long score);
	~GameOverScreen();
	/*virtual bool init();
	static cocos2d::CCScene* scene(long long score);*/


	void setScore(long long score);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

	void setupLabel();

	void update(float dt);

private:
	long long score;
	Keyboard* keyboard;

	//CREATE_FUNC(GameOverScreen);

	void setupBackground();

};

