#include "stdafx.h"
#include "mapTool.h"

HRESULT mapTool::init()
{
	setUp();

	return S_OK;
}

void mapTool::update()
{
	selectTileSet();
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_tileSet->drawTile(_currentTile.terrain, _currentTile.terrainFrameX, _currentTile.terrainFrameY);
	}
}

void mapTool::release()
{

}

void mapTool::render()
{

	IMAGEMANAGER->render("TR_Grass", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 300, 300);
}


void mapTool::selectTileSet()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < SAMPLEGRASSY*SAMPLEGRASSX; ++i)
		{
			if (PtInRect(&_TR_GRASS[i].tileRc, _ptMouse))
			{
				_currentTile.terrain = TR_GRASS;
				_currentTile.terrainFrameX = _TR_GRASS[i].terrainFrameX;
				_currentTile.terrainFrameY = _TR_GRASS[i].terrainFrameY;
			}
		}
	}

}

void mapTool::setUp()
{
	_ctrSelect = CTRL_TERRAINDRAW;

	_currentTile.terrain = TR_NONE;
	_currentTile.terrainFrameX = 0;
	_currentTile.terrainFrameY = 0;


	for (int y = 0; y < SAMPLEGRASSY; ++y)
	{
		for (int x = 0; x < SAMPLEGRASSX; ++x)
		{
			_TR_GRASS[x + y * SAMPLEGRASSX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 300 + x * TILESIZE, 300 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameX = x;
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameY = y;
		}
	}

	for (int y = 0; y < SAMPLEKINGDOMY; ++y)
	{
		for (int x = 0; x < SAMPLEKINGDOMX; ++x)
		{
			_TR_KD[x + y * SAMPLEKINGDOMX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 300 + x * TILESIZE, 300 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameX = x;
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameY = y;
		}
	}

	for (int y = 0; y < SAMPLEMTY; ++y)
	{
		for (int x = 0; x < SAMPLEMTX; ++x)
		{
			_TR_MT[x + y * SAMPLEMTX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 300 + x * TILESIZE, 300 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_MT[x + y * SAMPLEMTX].terrainFrameX = x;
			_TR_MT[x + y * SAMPLEMTX].terrainFrameY = y;
		}
	}
}
