#include "Constants.h"

// Added HP/Stats and HP bar sprite
class Creature : public CCSprite{
public:
	Creature(int hp, int maxHp);

private:
	int hp;
	int maxHp;
};

