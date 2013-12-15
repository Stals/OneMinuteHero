#include "BoardCreator.h"

#include "Wall.h"
#include "EmptyTile.h"
#include "Stairs.h"
#include <algorithm>

void BoardCreator::create(std::vector<std::vector<BoardTile*> >& tiles)
{
	int width = 15;
	int height = 18;

	tiles.resize(width);

	for(int x = 0; x < width; ++x){
		tiles[x].resize(height);
		for(int y = 0; y < height; ++y){
			
			int r = rand() % 5;
			
			if(r == 0){
				BoardTile* tile = new Wall;
				tiles[x][y] = tile;

			}else{
				BoardTile* tile = new EmptyTile;
				tiles[x][y] = tile;
			}
		}
	}

}

