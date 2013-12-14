#pragma once

#include <vector>

#include "Tile.h"
#include "Player.h"
#include "Monster.h"

// TODO ������ � board ����� ������ � �����? (� � ������ �� ������� ������)
class Board : public CCSprite{
public:
	Board(int width, int height);
	void addPlayer(Player* player, int x, int y);

	// returns true if moved (was walkable, and no monsters there)
	bool movePlayerTo(int x, int y);

private:
	Player* player;
	std::vector<Monster*> monsters;

	// ������� ������ � ������
	int tilesWidth;
	int tilesHeight;
	std::vector<std::vector<BoardTile*> > tiles;

	void setupTiles(int width, int height);
	void addMonsters();
	void addStairs(int x, int y);

	void setPosition(CCSprite* sprite, int tileX, int tileY);
	bool isMonsterOn(int x, int y);
};
