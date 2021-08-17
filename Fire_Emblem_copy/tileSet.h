#pragma once
#include "gameNode.h"
#define TILESIZE 48

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

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
	string getName(int tilex, int tiley) { return _tiles[tilex][tiley].name; }
	int getMove(int tilex, int tiley) { return _tiles[tilex][tiley].isMove; }
	int getDef(int tilex, int tiley) { return _tiles[tilex][tiley].def; }
	int getAvo(int tilex, int tiley) { return _tiles[tilex][tiley].avo; }
};

