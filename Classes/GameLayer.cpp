#include "GameLayer.h"

USING_NS_CC;
#define HALF_SPRITE_SIZE 15.5f
#define BOARD_OFFSET_X HALF_SPRITE_SIZE + 10
#define BOARD_OFFSET_Y HALF_SPRITE_SIZE*5 + 14

#define FIRE_AOE_DAMAGE 9
#define HEAL_SKILL_AMOUNT 25

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

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	setupKeyboard();
	setupBackground();
	setupPlayer();
	createBoard();

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
	keyboard = new Keyboard;
}


void GameLayer::update(float delta )
{
	processKeyboardInputs();
}

void GameLayer::setupPlayer()
{
	player = new Player(100, 4);
	player->retain();
}

void GameLayer::createBoard()
{
	if(board){
		this->removeChild(board);
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	board = new Board(15, 18);
	board->setPositionX(BOARD_OFFSET_X);
	board->setPositionY(BOARD_OFFSET_Y);
	
	this->addChild(board, zBoard);
	board->addPlayer(player, player->getTileX(), player->getTileY());
	board->setPlayerOnStairsCallback(CallbackData(this, menu_selector(GameLayer::playerOnStairsCallback)));
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
	CCMenuItemSprite *skill_button = CCMenuItemSprite::create(skillUnselected, skillSelected, skillUnselected,
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
	 monster->substractHp(player->getDamage());
	 if(!monster->isDead()){
		 // show animation of player attacking enemy		 
		 // TODO можно пройтись по всем монстрам вокруг игрока а не только тот которого ты трогаеш
		 player->substractHp(monster->getDamage());

		if(player->isDead()){
			// show dead screen
		}

	 }else{
		// TODO give EXP

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
	 if(playerSkill == SkillType::Fire){
		 useFireSkill();
	 }else if(playerSkill == SkillType::Heal){
		 useHealSkill();
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
					board->removeMonster(monster);
				}
			}
		}
	}

 }

 void GameLayer::useHealSkill()
 {
	 player->addHp(HEAL_SKILL_AMOUNT, true);
 }
