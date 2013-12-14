#include "Board.h"
#include "Wall.h"
#include "EmptyTile.h"

#define OFFSET_X 31
#define OFFSET_Y 30.7f

Board::Board(int width, int height):tilesWidth(width), tilesHeight(height){
	CCSprite::init();
	autorelease();

	this->setContentSize(CCSize(width * OFFSET_X, height * OFFSET_Y));
	this->setAnchorPoint(ccp(0,0));
	setupTiles(width, height);	
	addMonsters();
}


void Board::setupTiles(int width, int height)
{
	tiles.resize(width);

	for(int x = 0; x < width; ++x){
		tiles[x].resize(height);
		for(int y = 0; y < height; ++y){
			
			int r = rand() % 5;
			
			if(r == 0){
				BoardTile* tile = new Wall;
				tiles[x][y] = tile;
				setPosition(tile, x, y);
				addChild(tile);
			}else{
				BoardTile* tile = new EmptyTile;
				tiles[x][y] = tile;
				setPosition(tile, x, y);
				addChild(tile);
			}
		}	
	}
}


void Board::addMonsters()
{
	for(int x = 0; x < tilesWidth; ++x){
		for(int y = 0; y < tilesHeight; ++y){
			if(tiles[x][y]->isWalkable()){
				int r = rand() % 10;
				if(r == 0){
					Monster* monster = new Monster(10);
					setPosition(monster, x, y);
					monster->setTilePosition(x, y);
					addChild(monster);
					monsters.push_back(monster);
				}
			}
		}
	}
}


void Board::addPlayer(Player* player, int x, int y)
{
	this->player = player;
	setPosition(player, x, y);
	addChild(player);
}

bool Board::movePlayerTo(int x, int y)
{
	if(x < 0 || x > tilesWidth-1) return false;
	if(y < 0 || y > tilesHeight-1) return false;
	if(isMonsterOn(x, y)) return false;

	// TODO и там не монстров
	if(tiles[x][y]->isWalkable()){
		setPosition(player, x, y);
		player->setTilePosition(x, y);
		return true;
	}

	return false;
}

void Board::setPosition(CCSprite* sprite, int tileX, int tileY)
{
	sprite->setPositionX(tileX * OFFSET_X);
	sprite->setPositionY(tileY * OFFSET_Y);
}

bool Board::isMonsterOn(int x, int y)
{
	for(size_t i = 0; i < monsters.size(); ++i){
		if((monsters[i]->getTileX() == x) && (monsters[i]->getTileY() == y)){
			return true;
		} 
	}
	return false;
}

