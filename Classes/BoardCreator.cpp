#include "BoardCreator.h"

#include "Wall.h"
#include "EmptyTile.h"
#include "Stairs.h"
#include <algorithm>
#include <fstream>
#include "StringExtension.h"

#define LEVELS 5

void BoardCreator::create(std::vector<std::vector<BoardTile*> >& tiles)
{
	int width = 15;
	int height = 18;

	std::string filename = "levels/";
	filename.append(StringExtension::toString(rand()%LEVELS + 1)).append(".txt");

	std::ifstream infile(filename.c_str());

	std::vector<std::string> lines;
	std::string line;
	while (std::getline( infile, line))
	{
		lines.push_back(line);
		std::cout<<line<<std::endl;
	}

	/***/
	tiles.resize(width);
	for(int x = 0; x < width; ++x){
		tiles[x].resize(height);
		for(int y = 0; y < height; ++y){
			char tileChar = lines[y][x];
			BoardTile* tile = NULL;

			switch(tileChar){
			case '#':
				tile = new Wall;
				break;
			case ' ':
			default:
				tile = new EmptyTile;
				break;
			}

			tiles[x][y] = tile;
		}
	}
}

