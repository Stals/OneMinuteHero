#include "Board.h"
#include "Wall.h"
#include "EmptyTile.h"
#include "Stairs.h"
#include <algorithm>
#include "BoardCreator.h"

#define OFFSET_X 31
#define OFFSET_Y 30.7f

Board::Board(int width, int height, int floorNumber):tilesWidth(width), tilesHeight(height){
	CCSprite::init();
	autorelease();

	this->setContentSize(CCSize(width * OFFSET_X, height * OFFSET_Y));
	this->setAnchorPoint(ccp(0,0));
	setupTiles(width, height);	
	addMonsters(floorNumber);
	addStairs(rand()%width, rand()%height);
}

void Board::setPlayerOnStairsCallback(const CallbackData& callbackData)
{
	stairsCallData = callbackData;
}

void Board::setupTiles(int width, int height)
{
	// TODO вынести создание комнат и тд в отдельный класс
	/*
	
	}*/

	BoardCreator::create(tiles);

	for(int x = 0; x < width; ++x){
		for(int y = 0; y < height; ++y){
			BoardTile* tile = tiles[x][y];
			setPosition(tile, x, y);
			addChild(tile);		
		}
	}
}


void Board::addMonsters(int floorNumber)
{
	for(int x = 0; x < tilesWidth; ++x){
		for(int y = 0; y < tilesHeight; ++y){
			if(tiles[x][y]->isWalkable()){
				int r = rand() % 10;
				if(r == 0){
					Monster* monster = new Monster(10, 5, floorNumber / 1.5);
					setPosition(monster, x, y);
					monster->setTilePosition(x, y);
					addChild(monster, zCreature);
					monsters.push_back(monster);
				}
			}
		}
	}
}

void Board::addStairs(int x, int y)
{

	if(tiles[x][y]->isWalkable()){
		if(!this->isMonsterOn(x, y)){

			BoardTile* oldTile = tiles[x][y];
			removeChild(oldTile, true);
			Stairs* stairs = new Stairs;
			tiles[x][y] = stairs;
			setPosition(stairs, x, y);
			addChild(stairs);
			stairsPosition = TilePosition(x, y);
			return;
		}
	}
	addStairs(rand()%tilesWidth, rand()%tilesHeight);
}

void Board::addPlayer(Player* player, int x, int y)
{

	if(tiles[x][y]->isWalkable()){
		if(!this->isMonsterOn(x, y)){
			this->player = player;
			setPosition(player, x, y);
			addChild(player, zCreature);
			player->setTilePosition(x, y);
			return;
		}	
	}
	addPlayer(player, rand()%tilesWidth, rand()%tilesHeight);
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
		checkPlayerOnStairs();
		return true;
	}

	return false;
}

void Board::setPosition(CCSprite* sprite, int tileX, int tileY)
{
	sprite->setPositionX(tileX * OFFSET_X);
	sprite->setPositionY(tileY * OFFSET_Y);
}

Monster* Board::isMonsterOn(int x, int y)
{
	for(size_t i = 0; i < monsters.size(); ++i){
		if((monsters[i]->getTileX() == x) && (monsters[i]->getTileY() == y)){
			return monsters[i];
		} 
	}
	return false;
}

void Board::removeMonster(Monster* monster)
{
	monsters.erase(std::remove(monsters.begin(), monsters.end(), monster), monsters.end());
	this->removeChild(monster, true);
}

void Board::checkPlayerOnStairs()
{
	if((player->getTileX() == this->stairsPosition.x) && (player->getTileY() == this->stairsPosition.y)){
		stairsCallData.call();
	}
}

int Board::getTileWidth()
{
	return tilesWidth;
}

int Board::getTileHeight()
{
	return tilesHeight;
}
