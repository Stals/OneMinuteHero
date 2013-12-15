#pragma once

#include <vector>

#include "Tile.h"
#include "Player.h"
#include "Monster.h"

struct CallbackData{
	CallbackData(){}
	CallbackData(CCObject *target, SEL_MenuHandler callback):target(target), callback(callback){}

	CCObject *target;
	SEL_MenuHandler callback;

	void call(){
		if (target && callback){
			(target->*callback)(NULL);
		}
	}

};

struct TilePosition{
	TilePosition():x(0), y(0){}
	TilePosition(int x, int y):x(x), y(y){}

	int x;
	int y;
};

// TODO отдаем в board точки начала и конца? (и в начале он спавнит игрока)
class Board : public CCSprite{
public:
	Board(int width, int height, int floorNumber);
	void addPlayer(Player* player, int x, int y);

	// returns true if moved (was walkable, and no monsters there)
	bool movePlayerTo(int x, int y);
	void setPlayerOnStairsCallback(const CallbackData& callbackData);

	Monster* isMonsterOn(int x, int y);
	void removeMonster(Monster* monster);

	int getTileWidth();
	int getTileHeight();

private:
	CallbackData stairsCallData;
	TilePosition stairsPosition;
	Player* player;
	std::vector<Monster*> monsters;

	// сколько тайлов в ширину
	int tilesWidth;
	int tilesHeight;
	std::vector<std::vector<BoardTile*> > tiles;

	void setupTiles(int width, int height);
	void addMonsters(int floorNumber);
	void addStairs(int x, int y);

	void setPosition(CCSprite* sprite, int tileX, int tileY);
	void checkPlayerOnStairs();
};
