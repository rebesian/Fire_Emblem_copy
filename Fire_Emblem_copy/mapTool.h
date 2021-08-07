#pragma once
#include "gameNode.h"
#include <vector>
#include "tileSet.h"

#define SAMPLEGRASSX 6
#define SAMPLEGRASSY 7

#define SAMPLEKINGDOMX 3
#define SAMPLEKINGDOMY 7

#define SAMPLEMTX 8
#define SAMPLEMTY 6

struct tagSampleTile
{
	RECT tileRc;
	int terrainFrameX;
	int terrainFrameY;
};

struct tagCurrentTile
{
	TERRAIN terrain;
	int terrainFrameX;
	int terrainFrameY;
};

class mapTool : public gameNode
{
	
	int _ctrSelect; // 현재 선택할모드 
	tagCurrentTile _currentTile; //현재 선택된타일

	tagSampleTile _TR_GRASS[SAMPLEGRASSX *SAMPLEGRASSY];
	tagSampleTile _TR_KD[SAMPLEKINGDOMX *SAMPLEKINGDOMY];
	tagSampleTile _TR_MT[SAMPLEMTX * SAMPLEMTY];

	
	tileSet* _tileSet;

public:
	HRESULT init();
	void update();
	void release();
	void render();

	void selectTileSet();
	void setUp();

	void setLinkMemoryTileSet(tileSet* tileset) { _tileSet = tileset; }
};

