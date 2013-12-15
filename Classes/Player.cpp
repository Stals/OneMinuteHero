#include "Player.h"
#include "StringExtension.h"

Player::Player(int maxHp, int damage):Creature("hero.png", maxHp, damage, 1)
{
	score = 0;
	exp = 0;
	maxExp = 100;
}

void Player::addExp(int exp)
{
	score += (long long) exp * level;

	this->exp += exp;
	if(this->exp >= getMaxExp()){
		this->exp = 0;
		++level;
		addHp(getMaxHP() * 0.3f);

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
	return scaleVar(maxExp);
}

int Player::getHealAmount()
{
	return scaleVar(25);
}

int Player::getFireDamage()
{
	return scaleVar(11);
}

int Player::getStopTimeSeconds()
{
	return scaleVar(5);
}

float Player::getTimeSkillDelay()
{
	return 15;
}

float Player::getHealSkillDelay()
{
	return 10;
}

float Player::getFireSkillDelay()
{
	return 8;
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

long long Player::getScore()
{
	return score;
}