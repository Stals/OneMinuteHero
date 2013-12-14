#include "Board.h"
#include "Wall.h"

#define OFFSET_X 31
#define OFFSET_Y 30.7f

Board::Board(int width, int height):tilesWidth(width), tilesHeight(height){
	CCSprite::init();
	autorelease();

	this->setContentSize(CCSize(width * OFFSET_X, height * OFFSET_Y));
	this->setAnchorPoint(ccp(0,0));
	setupTiles(width, height);	
}


void Board::setupTiles(int width, int height)
{
	tiles.resize(width);

	for(int x = 0; x < width; ++x){
		tiles[x].resize(height);
		for(int y = 0; y < height; ++y){
			
			Entity* tile = new Wall;
			tiles[x][y] = tile;

			//tile->setAnchorPoint(ccp(0, 0));
			tile->setPositionX(x * OFFSET_X);
			tile->setPositionY(y * OFFSET_Y);
			addChild(tile);
		}	
	}
}
