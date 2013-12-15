#include "Player.h"
#include "StringExtension.h"

Player::Player(int maxHp, int damage):Creature("hero.png", maxHp, damage)
{
	exp = 0;
	maxExp = 100;
}

void Player::addExp(int exp)
{
	this->exp += exp;
	if(this->exp >= maxExp){
		this->exp = 0;
		++level;

		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/levelup.wav");
		showLevelupLabel();

	}else{
		showAddExpLabel(exp);
	}
}

int Player::getExp()
{
	return exp;
}

int Player::getMaxExp()
{
	return maxExp;
}

void Player::showAddExpLabel(int exp)
{
	CCLabelTTF* hpChangeLabel = CCLabelTTF::create(("+" + StringExtension::toString(exp)).c_str(), 
													"fonts/Quicksand_Bold", 12);
	hpChangeLabel->setColor(ccc3(57, 181, 74));
	addChild(hpChangeLabel);

	hpChangeLabel->setPosition(ccp(- 2 - this->getContentSize().width/2, 5));

	hpChangeLabel->runAction(CCMoveBy::create(1, ccp(0, 10)));
	CCSequence* seq = CCSequence::create(CCFadeOut::create(1),
										 CCCallFunc::create( hpChangeLabel, callfunc_selector(CCSprite::removeFromParent)),
										 NULL);
	hpChangeLabel->runAction(seq);
}

void Player::showLevelupLabel()
{
	CCLabelTTF* hpChangeLabel = CCLabelTTF::create("Level Up!", 
													"fonts/Quicksand_Bold", 12);
	hpChangeLabel->setColor(ccc3(57, 181, 74));
	addChild(hpChangeLabel);

	hpChangeLabel->setPosition(ccp(0, 15));

	hpChangeLabel->runAction(CCMoveBy::create(1.5f, ccp(0, 10)));
	CCSequence* seq = CCSequence::create(CCFadeOut::create(1.5f),
										 CCCallFunc::create( hpChangeLabel, callfunc_selector(CCSprite::removeFromParent)),
										 NULL);
	hpChangeLabel->runAction(seq);
}