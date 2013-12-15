#pragma once
#include "Tile.h"
#include <vector>

class BoardCreator{
public:

	static void create(std::vector<std::vector<BoardTile*> >& tiles);

private:
	static int countLevels();
};
