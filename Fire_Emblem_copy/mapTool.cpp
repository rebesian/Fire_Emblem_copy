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
	char str[3];
	Rectangle(getMemDC(), leftCatalog);
	sprintf_s(str , "<");
	TextOut(getMemDC(), leftCatalog.left+6, leftCatalog.top+6, str, strlen(str));
	Rectangle(getMemDC(), rightCatalog);
	sprintf_s(str, ">");
	TextOut(getMemDC(), rightCatalog.left+6 ,rightCatalog.top+6, str, strlen(str));
	char label[123];


	if (_catalog == GRASS)
	{
		sprintf_s(label, "GRASS");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_Grass", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 150, 100);
	}
	else if (_catalog == KINGDOM)
	{
		sprintf_s(label, "KINGDOM");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_KingDom", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("TR_KingDom")->getWidth() - 150, 100);
	}
	else if (_catalog == MOUNTIN)
	{
		sprintf_s(label, "MOUNTIN");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_MT", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("TR_MT")->getWidth() - 150, 100);
	}


}


void mapTool::selectTileSet()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_catalog == GRASS) 
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
		else if (_catalog == KINGDOM) 
		{
			for (int i = 0; i < SAMPLEKINGDOMY*SAMPLEKINGDOMX; ++i)
			{
				if (PtInRect(&_TR_KD[i].tileRc, _ptMouse))
				{
					_currentTile.terrain = TR_KINGDOM;
					_currentTile.terrainFrameX = _TR_KD[i].terrainFrameX;
					_currentTile.terrainFrameY = _TR_KD[i].terrainFrameY;
				}
			}
		}
		else if (_catalog == MOUNTIN)
		{
			for (int i = 0; i < SAMPLEMTY*SAMPLEMTX; ++i)
			{
				if (PtInRect(&_TR_MT[i].tileRc, _ptMouse))
				{
					_currentTile.terrain = TR_MOUNTIN;
					_currentTile.terrainFrameX = _TR_MT[i].terrainFrameX;
					_currentTile.terrainFrameY = _TR_MT[i].terrainFrameY;
				}
			}
		}

		if (PtInRect(&leftCatalog, _ptMouse))
		{
			if (_catalog == GRASS)
			{
				_catalog = MOUNTIN;
			}
			else if (_catalog == MOUNTIN)
			{
				_catalog = KINGDOM;
			}
			else if (_catalog == KINGDOM)
			{
				_catalog = GRASS;
			}
		}
		else if (PtInRect(&rightCatalog, _ptMouse))
		{
			if (_catalog == GRASS)
			{
				_catalog = KINGDOM;
			}
			else if (_catalog == KINGDOM)
			{
				_catalog = MOUNTIN;
			}
			else if (_catalog == MOUNTIN)
			{
				_catalog = GRASS;
			}
		}
	}
}

void mapTool::setUp()
{
	_catalog = GRASS;

	_ctrSelect = CTRL_TERRAINDRAW;

	_currentTile.terrain = TR_NONE;
	_currentTile.terrainFrameX = 0;
	_currentTile.terrainFrameY = 0;

	leftCatalog = RectMakeCenter(TILESIZE * 20 + 150, 50, 25, 25);
	rightCatalog = RectMakeCenter(TILESIZE * 20 + 350, 50, 25, 25);



	for (int y = 0; y < SAMPLEGRASSY; ++y)
	{
		for (int x = 0; x < SAMPLEGRASSX; ++x)
		{
			_TR_GRASS[x + y * SAMPLEGRASSX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_Grass")->getWidth() - 150 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameX = x;
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameY = y;
		}
	}



	for (int y = 0; y < SAMPLEKINGDOMY; ++y)
	{
		for (int x = 0; x < SAMPLEKINGDOMX; ++x)
		{
			_TR_KD[x + y * SAMPLEKINGDOMX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_KingDom")->getWidth() - 150 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameX = x;
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameY = y;
		}
	}



	for (int y = 0; y < SAMPLEMTY; ++y)
	{
		for (int x = 0; x < SAMPLEMTX; ++x)
		{
			_TR_MT[x + y * SAMPLEMTX].tileRc = RectMake(WINSIZEX - IMAGEMANAGER->findImage("TR_MT")->getWidth() - 150 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_MT[x + y * SAMPLEMTX].terrainFrameX = x;
			_TR_MT[x + y * SAMPLEMTX].terrainFrameY = y;
		}
	}


}
