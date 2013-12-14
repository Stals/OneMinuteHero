#pragma once

#include <vector>

#include "Entity.h"

class Board : public CCSprite{
public:
	Board(int width, int height);

private:
	// ������� ������ � ������
	int tilesWidth;
	int tilesHeight;
	std::vector<std::vector<Entity*> > tiles;

	void setupTiles(int width, int height);

	void addPlayer(int x, int y);
};
