#pragma once

#include "Constants.h"
#include "Keyboard.h"

#include "Board.h"
#include "ProgressBar.h"
#include "Timer.h"


class GameLayer : public cocos2d::CCLayer
{
public:
	~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	void update(float dt);	

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	void setSkill(SkillType skillType);

private:
	int floor;

	Keyboard* keyboard;
	Board* board;
	Player* player;
	SkillType playerSkill;
	ProgressBar* hpBar;
	ProgressBar* expBar;
	TimerSprite* timer;
	CCLabelTTF* levelLabel;

	// implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	void setupBackground();
	void setupKeyboard();
	void setupPlayer();
	void createBoard();
	void setupSkillButton();
	void setupBars();
	void setupLevelLabel();
	void setupTimer();

	void processKeyboardInputs();

	void playerOnStairsCallback(CCObject* pSender);

	void movePlayer(int x, int y);
	void fightMonster(Monster* monster);

	void useSkill(CCObject* pSender);
	void useFireSkill();
	void useHealSkill();
	void useTimeSkill();

	void updatePlayerHP();
	void updatePlayerExp();

	void showGameOver(CCObject* pSender);
};
