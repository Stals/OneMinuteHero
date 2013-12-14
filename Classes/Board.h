#pragma once

#include <vector>

#include "Tile.h"


// TODO отдаем в board точки начала и конца? (и в начале он спавнит игрока)
class Board : public CCSprite{
public:
	Board(int width, int height);

private:
	// сколько тайлов в ширину
	int tilesWidth;
	int tilesHeight;
	std::vector<std::vector<BoardTile*> > tiles;

	void setupTiles(int width, int height);

	void addPlayer(int x, int y);
};
