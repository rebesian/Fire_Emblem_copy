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
		if (endX==0 &&endY==0)
			_tileSet->drawTile(_currentTile.terrain, _currentTile.terrainFrameX, _currentTile.terrainFrameY);
		else
			_tileSet->drawTile(_currentTile.terrain, startX, startY, endX, endY);

	}
	_tileSet->update();

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

	//SetBkMode(getMemDC(), TRANSPARENT);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	HPEN myPen = (HPEN)CreatePen(0, 0, RGB(255, 255, 255));
	SelectObject(getMemDC(), myPen);
	switch (_catalog)
	{
	case GRASS:
		sprintf_s(label, "GRASS");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_Grass", getMemDC(), WINSIZEX - 400, 100);
		for (int i = 0; i < SAMPLEGRASSX *SAMPLEGRASSY; ++i)
		{
			Rectangle(getMemDC(), _TR_GRASS[i].tileRc);
		}
		break;
	case KINGDOM:
		sprintf_s(label, "KINGDOM");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_KingDom", getMemDC(), WINSIZEX - 400, 100);
		for (int i = 0; i < SAMPLEKINGDOMX *SAMPLEKINGDOMY; ++i)
		{
			Rectangle(getMemDC(), _TR_KD[i].tileRc);
		}
		break;
	case MOUNTIN:
		sprintf_s(label, "MOUNTIN");
		TextOut(getMemDC(), leftCatalog.right + 50, leftCatalog.top + 6, label, strlen(label));
		IMAGEMANAGER->render("TR_MT", getMemDC(), WINSIZEX - 400, 100);
		for (int i = 0; i < SAMPLEMTX *SAMPLEMTY; ++i)
		{
			Rectangle(getMemDC(), _TR_MT[i].tileRc);
		}
		break;
	}
	DeleteObject(myPen);
	for (int i = 0; i < _picking.size(); i++)
	{

		Rectangle(getMemDC(), _picking[i].rc);
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
	//ÇÇÅ·
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_picking.clear();
		startX = startY = endX = endY = 0;
		if (_catalog == GRASS)
		{
			for (int i = 0; i < SAMPLEGRASSY*SAMPLEGRASSX; ++i)
			{
				if (PtInRect(&_TR_GRASS[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					startX = _TR_GRASS[i].terrainFrameX;
					startY = _TR_GRASS[i].terrainFrameY;
					_currentTile.terrain = TR_GRASS;
					//pick.indexX = _TR_GRASS[i].terrainFrameX;
					//pick.indexY = _TR_GRASS[i].terrainFrameY;
					//pick.rc = _TR_GRASS[i].tileRc;
					//_picking.push_back(pick);
				}
			}
		}
		else if (_catalog == KINGDOM)
		{
			for (int i = 0; i < SAMPLEKINGDOMY*SAMPLEKINGDOMX; ++i)
			{
				if (PtInRect(&_TR_KD[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					startX = _TR_KD[i].terrainFrameX;
					startY = _TR_KD[i].terrainFrameY;
					_currentTile.terrain = TR_KINGDOM;
					//pick.indexX = _TR_KD[i].terrainFrameX;
					//pick.indexY = _TR_KD[i].terrainFrameY;
					//pick.rc = _TR_KD[i].tileRc;
					//_picking.push_back(pick);
				}
			}
		}
		else if (_catalog == MOUNTIN)
		{
			for (int i = 0; i < SAMPLEMTY*SAMPLEMTX; ++i)
			{
				if (PtInRect(&_TR_MT[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					startX = _TR_MT[i].terrainFrameX;
					startY = _TR_MT[i].terrainFrameY;
					_currentTile.terrain = TR_MOUNTIN;
					//pick.indexX = _TR_MT[i].terrainFrameX;
					//pick.indexY = _TR_MT[i].terrainFrameY;
					//pick.rc = _TR_MT[i].tileRc;
					//_picking.push_back(pick);
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

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		if (_catalog == GRASS) 
		{
			for (int i = 0; i < SAMPLEGRASSY*SAMPLEGRASSX; ++i)
			{
				if (PtInRect(&_TR_GRASS[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					endX = _TR_GRASS[i].terrainFrameX;
					endY = _TR_GRASS[i].terrainFrameY;
					//pick.indexX = _TR_GRASS[i].terrainFrameX;
					//pick.indexY = _TR_GRASS[i].terrainFrameY;
					//pick.rc = _TR_GRASS[i].tileRc;
			
				}
			}
		}
		else if (_catalog == KINGDOM) 
		{
			for (int i = 0; i < SAMPLEKINGDOMY*SAMPLEKINGDOMX; ++i)
			{
				if (PtInRect(&_TR_KD[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					endX = _TR_KD[i].terrainFrameX;
					endY = _TR_KD[i].terrainFrameY;
					//pick.indexX = _TR_KD[i].terrainFrameX;
					//pick.indexY = _TR_KD[i].terrainFrameY;
					//pick.rc = _TR_KD[i].tileRc;
					//_picking.push_back(pick);
				}
			}
		}
		else if (_catalog == MOUNTIN)
		{
			for (int i = 0; i < SAMPLEMTY*SAMPLEMTX; ++i)
			{
				if (PtInRect(&_TR_MT[i].tileRc, _ptMouse))
				{
					//tagPicking pick;
					endX = _TR_MT[i].terrainFrameX;
					endY = _TR_MT[i].terrainFrameY;
					//pick.indexX = _TR_MT[i].terrainFrameX;
					//pick.indexY = _TR_GRASS[i].terrainFrameY;
					//pick.rc = _TR_MT[i].tileRc;
					//_picking.push_back(pick);
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		
		for (int y = startY; y <= endY; ++y)
		{
			for (int x = startX; x <= endX; ++x)
			{
				HPEN myPen = (HPEN)CreatePen(0, 0, RGB(0, 0, 255));
				SelectObject(getMemDC(), myPen);
				tagPicking _pick;
				_pick.indexX = x;
				_pick.indexY = y;
				_pick.rc = RectMake(WINSIZEX - 400 + x * TILESIZE, 100 + y * TILESIZE, TILESIZE, TILESIZE);
				_pick.catalog = _currentTile.terrain;
				_picking.push_back(_pick);
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
			_TR_GRASS[x + y * SAMPLEGRASSX].tileRc = RectMake(WINSIZEX - 400 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameX = x;
			_TR_GRASS[x + y * SAMPLEGRASSX].terrainFrameY = y;
		}
	}



	for (int y = 0; y < SAMPLEKINGDOMY; ++y)
	{
		for (int x = 0; x < SAMPLEKINGDOMX; ++x)
		{
			_TR_KD[x + y * SAMPLEKINGDOMX].tileRc = RectMake(WINSIZEX - 400 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameX = x;
			_TR_KD[x + y * SAMPLEKINGDOMX].terrainFrameY = y;
		}
	}



	for (int y = 0; y < SAMPLEMTY; ++y)
	{
		for (int x = 0; x < SAMPLEMTX; ++x)
		{
			_TR_MT[x + y * SAMPLEMTX].tileRc = RectMake(WINSIZEX - 400 + x * TILESIZE, 100 + y * TILESIZE,
				TILESIZE, TILESIZE);
			_TR_MT[x + y * SAMPLEMTX].terrainFrameX = x;
			_TR_MT[x + y * SAMPLEMTX].terrainFrameY = y;
		}
	}

}