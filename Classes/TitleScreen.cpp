#include "TitleScreen.h"
#include "GameLayer.h"

TitleScreen::~TitleScreen()
{
}

CCScene* TitleScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScreen *layer = TitleScreen::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);

    // return the scene
    return scene;
}

bool TitleScreen::init()
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
	setupButtons();
	setTouchEnabled(true);
	
	return true;
}

void TitleScreen::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* bgSprite = CCSprite::create("titlescreen.png");	
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite, zBackground);
}

void TitleScreen::setupButtons()
{
	CCSprite *healUnselected = CCSprite::create("healSkill.png");
	CCSprite *healSelected = CCSprite::create("healSkill.png");
	CCMenuItemSprite *heal_button = CCMenuItemSprite::create(healUnselected, healSelected, healUnselected,
		this, menu_selector(TitleScreen::healChosen));


	CCSprite *fireUnselected = CCSprite::create("fireSkill.png");
	CCSprite *fireSelected = CCSprite::create("fireSkill.png");
	CCMenuItemSprite *fire_button = CCMenuItemSprite::create(fireUnselected, fireSelected, fireUnselected,
		this , menu_selector(TitleScreen::fireChosen));

	CCSprite *timeUnselected = CCSprite::create("timeSkill.png");
	CCSprite *timeSelected = CCSprite::create("timeSkill.png");
	CCMenuItemSprite *time_button = CCMenuItemSprite::create(timeUnselected, timeSelected, timeUnselected,
		this , menu_selector(TitleScreen::timeChosen));


	CCMenu* menu = CCMenu::create(heal_button, fire_button, time_button, NULL);
	menu->alignItemsHorizontallyWithPadding(20);


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// Set position of menu to be below the title text
	menu->setPosition(ccp(winSize.width/2, (winSize.height/2) + 63));

	// Add menu to layer
	this->addChild(menu, 2);
}

void TitleScreen::healChosen(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void TitleScreen::fireChosen(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}

void TitleScreen::timeChosen(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
}
