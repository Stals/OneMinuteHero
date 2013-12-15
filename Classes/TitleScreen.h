#pragma once

#include "Constants.h"

class TitleScreen : public CCLayer{
public:
	~TitleScreen();
	virtual bool init();
	static cocos2d::CCScene* scene();

private:
	CREATE_FUNC(TitleScreen);

	void setupBackground();
	void setupButtons();

	void healChosen(CCObject* pSender);
	void fireChosen(CCObject* pSender);
	void timeChosen(CCObject* pSender);
};
