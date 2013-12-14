#pragma once

#include <vector>

#include "Tile.h"


// TODO ������ � board ����� ������ � �����? (� � ������ �� ������� ������)
class Board : public CCSprite{
public:
	Board(int width, int height);

private:
	// ������� ������ � ������
	int tilesWidth;
	int tilesHeight;
	std::vector<std::vector<BoardTile*> > tiles;

	void setupTiles(int width, int height);

	void addPlayer(int x, int y);
};
