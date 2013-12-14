#include "Creature.h"
#include "StringExtension.h"

Creature::Creature(const char* filename, int maxHp, int damage): tileX(0), tileY(0), hp(maxHp), maxHp(maxHp), damage(damage)
{
	CCSprite::init();
	//autorelease();

	CCSprite* sprite = CCSprite::create(filename);
	this->setContentSize(sprite->getContentSize());
	this->setAnchorPoint(ccp(0,0));
	addChild(sprite);
	
	//setupHPBar();
}

void Creature::setTileX(int x)
{
	tileX = x;
}

void Creature::setTileY(int y)
{
	tileY = y;
}

void Creature::setTilePosition(int x, int y)
{
	tileX = x;
	tileY = y;
}

int Creature::getTileX()
{
	return tileX;
}

int Creature::getTileY()
{
	return tileY;
}


void Creature::substractHp(int hp, bool animated)
{
	this->hp -= hp;

	CCLabelTTF* ttf1 = CCLabelTTF::create(StringExtension::toString(-1 * hp).c_str(), "fonts/Quicksand_Bold", 12);
                                      //CCSizeMake(245, 32), kCCTextAlignmentCenter);

	ttf1->setPositionX(2 + this->getContentSize().width/2);
	this->addChild(ttf1);

	ttf1->runAction(CCMoveBy::create(0.5f, ccp(0, -10)));
	ttf1->runAction(CCFadeOut::create(0.5f));
	//ttf1->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -10), );

}

void Creature::addHp(int hp, bool animated)
{
	if(this->hp + hp > this->maxHp){
		this->hp = this->maxHp;
	}else{
		this->hp += hp;
	}
}

int Creature::getDamage()
{
	return damage;
}

bool Creature::isDead(){
	return hp <= 0;
}

void Creature::setupHPBar()
{
	/*hpBar = new ProgressBar(CCSprite::create("hpBarEmpty.png"), CCSprite::create("hpBarFull.png"));
	hpBar->setPosition(ccp(getContentSize().width/2, 2 + getContentSize().height/2));
	
	this->addChild(hpBar);
	hpBar->setVisible(false);*/
}
