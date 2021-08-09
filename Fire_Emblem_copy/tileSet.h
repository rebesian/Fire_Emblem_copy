#pragma once
#include "gameNode.h"
#define TILESIZE 48

class mapTool;

struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int indexX;
	int indexY;
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

	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
	
};

