#pragma once
#include "gameNode.h"
#define TILESIZE 48

struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

class tileSet : public gameNode
{
private:

	int _tileX, _tileY;
	vector<vector<tagTile>> _tiles;
	
public:

	HRESULT init();
	void update();
	void release();
	void render();

	void setup();
	
	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }
};

