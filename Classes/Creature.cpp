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


	CCLabelTTF* hpChangeLabel = CCLabelTTF::create(StringExtension::toString(-1 * hp).c_str(), 
													"fonts/Quicksand_Bold", 12);
	addChild(hpChangeLabel);

	hpChangeLabel->setPosition(ccp(2 + this->getContentSize().width/2, 0));

	hpChangeLabel->runAction(CCMoveBy::create(0.5f, ccp(0, -10)));
	CCSequence* seq = CCSequence::create(CCFadeOut::create(0.5f),
										 CCCallFunc::create( hpChangeLabel, callfunc_selector(CCSprite::removeFromParent)),
										 NULL);
	hpChangeLabel->runAction(seq);
}

void Creature::addHp(int hp, bool animated)
{
	const int beforeHP = this->hp;

	if(this->hp + hp > this->maxHp){
		this->hp = this->maxHp;
	}else{
		this->hp += hp;
	}

	const int newHP = this->hp;
	const int diff = newHP - beforeHP;


	CCLabelTTF* hpChangeLabel = CCLabelTTF::create(("+" + StringExtension::toString(diff)).c_str(), 
													"fonts/Quicksand_Bold", 12);
	hpChangeLabel->setColor(ccc3(255, 0, 16));
	addChild(hpChangeLabel);

	hpChangeLabel->setPosition(ccp(2 + this->getContentSize().width/2, 5));

	hpChangeLabel->runAction(CCMoveBy::create(1, ccp(0, 10)));
	CCSequence* seq = CCSequence::create(CCFadeOut::create(1),
										 CCCallFunc::create( hpChangeLabel, callfunc_selector(CCSprite::removeFromParent)),
										 NULL);
	hpChangeLabel->runAction(seq);

}

int Creature::getHP()
{
	return hp;
}

int Creature::getMaxHP()
{
	return maxHp;
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

