#include "GameOverScreen.h"
#include "GameLayer.h"
#include "TitleScreen.h"
#include "StringExtension.h"

GameOverScreen::~GameOverScreen()
{
}

CCScene* GameOverScreen::scene(long long score)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOverScreen *layer = GameOverScreen::create();
	layer->setScore(score);

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

void GameOverScreen::setScore(long long score)
{
	this->score = score;
		setupLabel();
}

void GameOverScreen::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::create("gameOverScreen.png");	
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite, zBackground);
}

void GameOverScreen::setupLabel()
{
	CCLabelTTF* label = CCLabelTTF::create((StringExtension::toString(score)).c_str(), 
													"fonts/Quicksand_Bold", 20);
	label->setColor(ccc3(250, 250, 250));
	addChild(label);

	label->setPosition(ccp(this->getContentSize().width/2, 422));

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
