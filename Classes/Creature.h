#include "Entity.h"

// Added HP/Stats and HP bar sprite
class Creature : public Entity{
public:
	Creature(int hp, int maxHp);

private:
	int hp;
	int maxHp;
};

