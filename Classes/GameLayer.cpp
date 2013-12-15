#include "GameLayer.h"
#include "GameOverScreen.h"
#include "TitleScreen.h"
#include "StringExtension.h"
#include "TutorialLayer.h"

USING_NS_CC;
#define HALF_SPRITE_SIZE 15.5f
#define BOARD_OFFSET_X HALF_SPRITE_SIZE + 10
#define BOARD_OFFSET_Y HALF_SPRITE_SIZE*5 + 14

#define FIRE_AOE_DAMAGE player->getFireDamage()
#define HEAL_SKILL_AMOUNT player->getHealAmount()
#define TIME_SKILL_DELAY player->getStopTimeSeconds()

#define SECONDS_PER_FLOOR 7

GameLayer::~GameLayer(){
	player->release();
}


CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    board = NULL;
	floor = 1;
	keyboard = NULL;

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	setupKeyboard();
	setupBackground();
	setupPlayer();
	setupBars();
	setupLevelLabel();

	updatePlayerHP();
	updatePlayerExp();

	setupTimer();
	createBoard();

	showTutorial();


	setTouchEnabled(true);
    scheduleUpdate();
	
	return true;
}

void GameLayer::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::create("background.png");	
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite, zBackground);
}


void GameLayer::setupKeyboard()
{
	
}


void GameLayer::update(float delta )
{
	updatePlayerHP();
	processKeyboardInputs();
}

void GameLayer::setupPlayer()
{
	player = new Player(5, 5);
	player->retain();
}

void GameLayer::createBoard()
{
	if(board){
		++floor;
		if(floor == 60){
			showVictorySceen(this);
			return;
		}


		this->removeChild(board);
		timer->addSeconds(SECONDS_PER_FLOOR);
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	board = new Board(15, 18, floor);
	board->setPositionX(BOARD_OFFSET_X);
	board->setPositionY(BOARD_OFFSET_Y);
	
	this->addChild(board, zBoard);
	board->addPlayer(player, player->getTileX(), player->getTileY());
	board->setPlayerOnStairsCallback(CallbackData(this, menu_selector(GameLayer::playerOnStairsCallback)));

	player->shceduleRegen();
	player->cleanLabels();
}

void GameLayer::setupBars()
{
	this->hpBar = new ProgressBar(CCSprite::create("hpBarEmpty.png"), CCSprite::create("hpBarFull.png"));
	this->expBar = new ProgressBar(CCSprite::create("expBarEmpty.png"), CCSprite::create("expBarFull.png"));

	hpBar->setPosition(ccp(hpBar->getContentSize().width + 91 +12, 60));
	expBar->setPosition(ccp(hpBar->getContentSize().width +91+ 12, 30));

	this->addChild(hpBar);
	this->addChild(expBar);
}

void GameLayer::setupLevelLabel()
{
	levelLabel = CCLabelTTF::create("Lv. 1", "fonts/Quicksand_Bold", 14);
	levelLabel->setColor(ccc3(0,0,0));
	this->addChild(levelLabel);
	levelLabel->setPosition(ccp(91 + 40 + 91, 30));
}

void GameLayer::setupTimer()
{
	timer = new TimerSprite(60, 30, ccc3(0,0,0));
	timer->setEndTimeCallback(this, menu_selector(GameLayer::showGameOver));

	timer->setPosition(ccp(390, -42));
	
	this->addChild(timer);	
}

void GameLayer::showTutorial()
{
	static bool tutorialShown = false;

	if(!tutorialShown){
		tutorialShown = true;

		addChild(new TutorialLayer(timer, &keyboard), zTutorial);
	}else{
		timer->start();
		keyboard = new Keyboard;
	}
}


void GameLayer::setSkill(SkillType skillType)
{
	playerSkill = skillType;
	setupSkillButton();
}

void GameLayer::setupSkillButton()
{
	std::string filename;
	switch(playerSkill){
	case Heal:
		filename = "healSkill.png"; break;
	case Fire:
		filename = "fireSkill.png"; break;
	case Time:
		filename = "timeSkill.png"; break;
	}



	CCSprite *skillUnselected = CCSprite::create(filename.c_str());
	CCSprite *skillSelected = CCSprite::create(filename.c_str());
	skill_button = CCMenuItemSprite::create(skillUnselected, skillSelected, skillUnselected,
		this, menu_selector(GameLayer::useSkill));

	CCMenu* menu = CCMenu::create(skill_button, NULL);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// Set position of menu to be below the title text
	menu->setPosition(ccp(winSize.width - 36, 49));

	// Add menu to layer
	this->addChild(menu, 2);
}

 void GameLayer::processKeyboardInputs()
 {
	 if(!keyboard) return;

	 if(keyboard->wasKeyPressed(InputKey::Key_ESC)){
		CCDirector::sharedDirector()->replaceScene(TitleScreen::scene());
		return;
	 }

	 if(keyboard->wasKeyPressed(InputKey::Key_Space)){
		useSkill(this);
		return;
	 }


	 int changeX = 0;
	 int changeY = 0;

	 if(keyboard->wasKeyPressed(InputKey::Key_Up) || keyboard->wasKeyPressed(InputKey::Key_W)){
		changeY = 1;
	}
	else if(keyboard->wasKeyPressed(InputKey::Key_Left) || keyboard->wasKeyPressed(InputKey::Key_A)){
		changeX = -1;
	}
	else if(keyboard->wasKeyPressed(InputKey::Key_Right) || keyboard->wasKeyPressed(InputKey::Key_D)){
		changeX = 1;
	}
	else if(keyboard->wasKeyPressed(InputKey::Key_Down) || keyboard->wasKeyPressed(InputKey::Key_S)){
		changeY = -1;
	}

	const int x = player->getTileX() + changeX;
	const int y = player->getTileY() + changeY;

	Monster* monster = board->isMonsterOn(x, y);
	if(monster){
		fightMonster(monster);
	}else{
		movePlayer(player->getTileX() + changeX, player->getTileY() + changeY);
	}	
 }

 void GameLayer::movePlayer(int x, int y)
 {
	 board->movePlayerTo(x, y);
 }

 void GameLayer::fightMonster(Monster* monster)
 {
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hit.wav");
	 monster->substractHp(player->getDamage());
	 if(!monster->isDead()){
		 // show animation of player attacking enemy		 
		 // TODO можно пройтись по всем монстрам вокруг игрока а не только тот которого ты трогаеш
		 player->substractHp(monster->getDamage());
		 updatePlayerHP();
		if(player->isDead()){
			// show dead screen
			this->showGameOver(this);
		}

	 }else{
		// TODO give EXP
		player->addExp(monster->getRewardExp());
		updatePlayerExp();
		updatePlayerHP();

		const int newX = monster->getTileX();
		const int newY = monster->getTileY();		
		board->removeMonster(monster);
		movePlayer(newX, newY);
	 }
 }

 void GameLayer::playerOnStairsCallback(CCObject* pSender)
 {
	 createBoard();
 }

 void GameLayer::useSkill(CCObject* pSender)
 {
	 if(!skill_button->isEnabled()) return;
	
	int delay = 0;
	bool success = true;
	 if(playerSkill == SkillType::Fire){
		 useFireSkill();
		 delay = player->getFireSkillDelay();
	 }else if(playerSkill == SkillType::Heal){
		 success = useHealSkill();
		 delay = player->getHealSkillDelay();
	 }else if(playerSkill == SkillType::Time){
		useTimeSkill();
		delay = player->getTimeSkillDelay();
	 }


	 if(success){
		CCSequence* seq = CCSequence::create(
							CCCallFunc::create( this, callfunc_selector(GameLayer::disableSkill)),
							CCDelayTime::create(delay),
							CCCallFunc::create( this, callfunc_selector(GameLayer::enableSkill)),
							NULL);
		this->runAction(seq);
	 }
 }

 void GameLayer::useFireSkill()
 {
	 CCSprite* fireAOE = CCSprite::create("fireAOE.png");
	fireAOE->setOpacity(200);
	fireAOE->setPosition(player->getPosition());
	board->addChild(fireAOE, zAOE);

	CCSequence* seq = CCSequence::create(CCFadeOut::create(0.5f),
									CCCallFunc::create( fireAOE, callfunc_selector(CCSprite::removeFromParent)),
									NULL);
	fireAOE->runAction(seq);


	const int startX = std::max(0, player->getTileX() - 1);
	const int endX = std::min(board->getTileWidth()-1, player->getTileX() + 1);

	const int endY = std::min(board->getTileHeight()-1, player->getTileY() + 1);
	const int startY = std::max(0, player->getTileY() - 1);

		

	for(int x = startX; x <= endX; ++x){
		for(int y = startY; y <= endY; ++y){
			Monster* monster = board->isMonsterOn(x, y);
			if(monster){
				monster->substractHp(FIRE_AOE_DAMAGE, true);
				if(monster->isDead()){
					player->addExp(monster->getRewardExp());
					updatePlayerExp();
					updatePlayerHP();
					board->removeMonster(monster);
				}
			}
		}
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/fire.wav");

 }

 bool GameLayer::useHealSkill()
 {
	 if(player->getHP() < player->getMaxHP()){
		 player->addHp(HEAL_SKILL_AMOUNT, true);
		 updatePlayerHP();
		 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/heal.wav");
		 return true;
	 }
	 return false;
 }

 void GameLayer::useTimeSkill()
 {
	timer->runAction(CCBlink::create(0.5f, 2));

	CCSequence* seq = CCSequence::create(
								CCCallFunc::create( timer, callfunc_selector(TimerSprite::stop)),
								CCDelayTime::create(TIME_SKILL_DELAY),
								CCCallFunc::create( timer, callfunc_selector(TimerSprite::start)),
								CCBlink::create(0.5f, 2),
								NULL);
	timer->runAction(seq);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/time.wav");
 }

void GameLayer::updatePlayerHP()
{
	hpBar->setPercent((player->getHP() / (double)player->getMaxHP()) * 100.f);
}

void GameLayer::updatePlayerExp()
{
	expBar->setPercent((player->getExp() / (double)player->getMaxExp()) * 100.f);
	levelLabel->setString(("Lv. " + StringExtension::toString(player->getLevel())).c_str());
}

void GameLayer::showGameOver(CCObject* pSender)
{
	delete keyboard;
	keyboard = NULL;

	this->addChild(new GameOverScreen(false, player->getScore(), floor), zGameover);
}

void GameLayer::showVictorySceen(CCObject* pSender)
{
	delete keyboard;
	keyboard = NULL;

	this->addChild(new GameOverScreen(true, player->getScore()), zGameover);
}

void GameLayer::enableSkill()
{
	skill_button->setEnabled(true);
	skill_button->setOpacity(255);
}

void GameLayer::disableSkill()
{
	skill_button->setEnabled(false);
	skill_button->setOpacity(127);
}

