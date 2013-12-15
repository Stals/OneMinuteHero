#include "GameOverScreen.h"
#include "GameLayer.h"
#include "TitleScreen.h"

GameOverScreen::~GameOverScreen()
{
}

CCScene* GameOverScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOverScreen *layer = GameOverScreen::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);

    // return the scene
    return scene;
}

bool GameOverScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	setupBackground();
	//setTouchEnabled(true);
	//this->registerWithTouchDispatcher();
	
	return true;
}

void GameOverScreen::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::create("gameOverScreen.png");	
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite, zBackground);
}


bool GameOverScreen::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCDirector::sharedDirector()->replaceScene(TitleScreen::scene());
	return true;
}

void GameOverScreen::onEnter(){
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
        CCLayer::onEnter();
}
void GameOverScreen::onExit(){
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        CCLayer::onExit();
}
