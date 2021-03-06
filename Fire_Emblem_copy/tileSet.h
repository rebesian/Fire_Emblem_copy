#pragma once
#include "gameNode.h"

class mapTool;

struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	string name;
	int terrainFrameX;
	int terrainFrameY;
	int indexX;
	int indexY;
	bool isMove = true;
	bool isPlayer;
	bool isEnemy;
	int def;
	int avo;
};

class tileSet : public gameNode
{
private:

	image* _tileBuffer;
	int _tileX, _tileY;
	vector<vector<tagTile>> _tiles;

public:

	HRESULT init();
	void update();
	void release();
	void render();

	void setup();
	void drawTile(TERRAIN _terrain, int frameX, int frameY);
	void drawTile(TERRAIN _terrain, int startx, int starty, int endx, int endy);
	void resizeTile(int tilex, int tiley);
	void save();
	void load();


	int getSizeX() { return _tileX; }
	int getSizeY() { return _tileY; }
	TERRAIN getTerrain(int tilex, int tiley) { return _tiles[tiley][tilex].terrain; }
	HDC getMapDC() {return _tileBuffer->getMemDC(); }
	image* getTileBuffer() { return _tileBuffer; }
	RECT getRect(int tilex, int tiley) { return _tiles[tiley][tilex].rc; }
	bool getIsEnemy(int tilex, int tiley) { return _tiles[tiley][tilex].isEnemy; }
	bool getIsPlayer(int tilex, int tiley) { return _tiles[tiley][tilex].isPlayer; }
	string getName(int tilex, int tiley) { return _tiles[tiley][tilex].name; }
	bool getMove(int tilex, int tiley) { return _tiles[tiley][tilex].isMove; }
	int getDef(int tilex, int tiley) { return _tiles[tiley][tilex].def; }
	int getAvo(int tilex, int tiley) { return _tiles[tiley][tilex].avo; }

	void setIsEnemy(int tilex, int tiley, bool istrue) { _tiles[tiley][tilex].isEnemy = istrue; }
	void setIsPlayer(int tilex, int tiley, bool istrue) { _tiles[tiley][tilex].isPlayer = istrue; }
};

