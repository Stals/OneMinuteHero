#include "Constants.h"

// Added HP/Stats and HP bar sprite
class Creature : public CCSprite{
public:
	Creature(int hp, int maxHp);
	void setTileX(int x);
	void setTileY(int y);
	void setTilePosition(int x, int y);

	int getTileX();
	int getTileY();

private:
	int tileX;
	int tileY;

	int hp;
	int maxHp;
};

