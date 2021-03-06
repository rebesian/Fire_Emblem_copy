#include "stdafx.h"
#include "mapTool.h"

HRESULT mapTool::init()
{
	ispick = isSizeX = isSizeY =false;
	return S_OK;
}

void mapTool::update()
{

	selectTileSet();
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if(PtInRect(&DRAW, _ptMouse)&& !_picking.empty())
			_tileSet->drawTile(_currentTile.terrain, startX, startY, endX, endY);
	}
	if (isSizeX)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			if (!resizeX.empty())
				resizeX.pop_back();
		}
		for (int i = 0; i < 10; ++i)
		{
			if (KEYMANAGER->isOnceKeyDown(char(i + 48)))
			{
				resizeX.append(to_string(char(i)));
			}
		}
	}
	if (isSizeY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			if (!resizeY.empty())
				resizeY.pop_back();
		}
		for (int i = 0; i < 10; ++i) 
		{
			if (KEYMANAGER->isOnceKeyDown(char(i + 48)))
			{
				resizeY.append(to_string(char(i)));
			}
		}
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
	
	char label[30];

	sprintf_s(label, "SAVE");
	TextOut(getMemDC(), save.left+20 , save.bottom + 6, label, strlen(label));
	IMAGEMANAGER->render("save", getMemDC(), save.left, save.top);

	sprintf_s(label, "LOAD");
	TextOut(getMemDC(), load.left+20 , load.bottom + 6, label, strlen(label));
	IMAGEMANAGER->render("load", getMemDC(), load.left, load.top);

	sprintf_s(label, "???? Ÿ??");
	TextOut(getMemDC(), SelectTileset.left + 110, SelectTileset.top - 30, label, strlen(label));
	Rectangle(getMemDC(), SelectTileset);

	//SetBkMode(getMemDC(), TRANSPARENT);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	HPEN myPen = (HPEN)CreatePen(0, 2, RGB(0, 0, 255));
	HPEN oldPen = (HPEN)CreatePen(0, 0, RGB(0, 0, 0));
	
	Rectangle(getMemDC(), DRAW);
	Rectangle(getMemDC(), resize);
	if (isSizeX)
	{
		SelectObject(getMemDC(), myPen);
		Rectangle(getMemDC(), sizeX);
		SelectObject(getMemDC(), oldPen);
	}
	else
	{
		Rectangle(getMemDC(), sizeX);
	}
	if (isSizeY)
	{
		SelectObject(getMemDC(), myPen);
		Rectangle(getMemDC(), sizeY);
		SelectObject(getMemDC(), oldPen);
	}
	else
	{
		Rectangle(getMemDC(), sizeY);
	}
	DrawText(getMemDC(), resizeX.c_str(), strlen(resizeX.c_str()), &sizeX, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DrawText(getMemDC(), resizeY.c_str(), strlen(resizeY.c_str()), &sizeY, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	
	sprintf_s(label, "sizeX");
	TextOut(getMemDC(), sizeX.left - 50, sizeX.top+10, label, strlen(label));
	sprintf_s(label, "sizeY");
	TextOut(getMemDC(), sizeY.left - 50, sizeY.top+10 , label, strlen(label));
	sprintf_s(label, "resize");
	DrawText(getMemDC(), label, strlen(label), &resize, DT_CENTER | DT_SINGLELINE | DT_VCENTER);


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

	if (ispick) {
		for (int y = startY; y <= endY; ++y)
		{
			for (int x = startX; x <= endX; ++x)
			{
				SelectObject(getMemDC(), myPen);
				switch (_catalog)
				{
				case GRASS:
					SelectObject(getMemDC(), myPen);
					Rectangle(getMemDC(), _TR_GRASS[x + SAMPLEGRASSX * y].tileRc);
					SelectObject(getMemDC(), oldPen);
					break;
				case KINGDOM:
					SelectObject(getMemDC(), myPen);
					Rectangle(getMemDC(), _TR_KD[x + SAMPLEKINGDOMX * y].tileRc);
					SelectObject(getMemDC(), oldPen);
					break;
				case MOUNTIN:
					SelectObject(getMemDC(), myPen);
					Rectangle(getMemDC(), _TR_MT[x + SAMPLEMTX * y].tileRc);
					SelectObject(getMemDC(), oldPen);
					break;
				}
			}
		}
	}

	if (!_picking.empty())
	{
		for (int i = 0; i < _picking.size(); ++i)
		{
			switch (_picking[i].catalog)
			{
			case TR_GRASS:
				IMAGEMANAGER->frameRender("TR_Grass", getMemDC(), 
					((SelectTileset.left + SelectTileset.right) / 2 - TILESIZE * (endX - startX+1)) + (i % (endX - startX + 1)) *  TILESIZE + 30 * (endX - startX),
					((SelectTileset.top + SelectTileset.bottom) / 2 - TILESIZE * (endY - startY+1)) + (i / (endX - startX + 1)) * TILESIZE + 30 * (endY - startY),
					_picking[i].indexX, _picking[i].indexY);
				break;
			case TR_KINGDOM:
				IMAGEMANAGER->frameRender("TR_KingDom", getMemDC(),
					((SelectTileset.left + SelectTileset.right) / 2 - TILESIZE * (endX - startX+1)) + (i % (endX - startX + 1)) * TILESIZE + 30 * (endX - startX ),
					((SelectTileset.top + SelectTileset.bottom) / 2 - TILESIZE * (endY - startY+1)) + (i / (endX - startX + 1)) * TILESIZE + 30 * (endY - startY),
					_picking[i].indexX, _picking[i].indexY);
				break;
			case TR_MOUNTIN:
				IMAGEMANAGER->frameRender("TR_MT", getMemDC(),
					((SelectTileset.left + SelectTileset.right) / 2 - TILESIZE * (endX - startX+1)) + (i % (endX - startX + 1)) * TILESIZE + 30 * (endX - startX),
					((SelectTileset.top + SelectTileset.bottom) / 2 - TILESIZE * (endY - startY+1)) + (i / (endX - startX + 1)) * TILESIZE + 30 * (endY - startY),
					_picking[i].indexX, _picking[i].indexY);
				break;
			}
		}
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

		if (PtInRect(&save, _ptMouse))
		{
			_tileSet->save();
		}

		if (PtInRect(&load, _ptMouse))
		{
			_tileSet->load();
		}


		if (PtInRect(&sizeX, _ptMouse))
		{
			if(!isSizeX)isSizeX = true;
			else isSizeX = false;
		}

		if (PtInRect(&sizeY, _ptMouse))
		{
			if(!isSizeY)isSizeY = true;
			else isSizeY = false;
		}
		if (PtInRect(&resize, _ptMouse))
		{
			_tileSet->resizeTile(stoi(resizeX), stoi(resizeY));
		}
	}


	//??ŷ
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_picking.clear();
		ispick = false;
		startX = startY = endX = endY = 0;
		if (_catalog == GRASS)
		{
			for (int i = 0; i < SAMPLEGRASSY*SAMPLEGRASSX; ++i)
			{
				if (PtInRect(&_TR_GRASS[i].tileRc, _ptMouse))
				{

					startX = _TR_GRASS[i].terrainFrameX;
					startY = _TR_GRASS[i].terrainFrameY;
					_currentTile.terrain = TR_GRASS;
				
				}
			}
		}
		else if (_catalog == KINGDOM)
		{
			for (int i = 0; i < SAMPLEKINGDOMY*SAMPLEKINGDOMX; ++i)
			{
				if (PtInRect(&_TR_KD[i].tileRc, _ptMouse))
				{

					startX = _TR_KD[i].terrainFrameX;
					startY = _TR_KD[i].terrainFrameY;
					_currentTile.terrain = TR_KINGDOM;
			
				}
			}
		}
		else if (_catalog == MOUNTIN)
		{
			for (int i = 0; i < SAMPLEMTY*SAMPLEMTX; ++i)
			{
				if (PtInRect(&_TR_MT[i].tileRc, _ptMouse))
				{
				
					startX = _TR_MT[i].terrainFrameX;
					startY = _TR_MT[i].terrainFrameY;
					_currentTile.terrain = TR_MOUNTIN;
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
					endX = _TR_GRASS[i].terrainFrameX;
					endY = _TR_GRASS[i].terrainFrameY;
					ispick = true;
			
				}
			}
		}
		else if (_catalog == KINGDOM) 
		{
			for (int i = 0; i < SAMPLEKINGDOMY*SAMPLEKINGDOMX; ++i)
			{
				if (PtInRect(&_TR_KD[i].tileRc, _ptMouse))
				{
					endX = _TR_KD[i].terrainFrameX;
					endY = _TR_KD[i].terrainFrameY;
					ispick = true;
				}
			}
		}
		else if (_catalog == MOUNTIN)
		{
			for (int i = 0; i < SAMPLEMTY*SAMPLEMTX; ++i)
			{
				if (PtInRect(&_TR_MT[i].tileRc, _ptMouse))
				{

					endX = _TR_MT[i].terrainFrameX;
					endY = _TR_MT[i].terrainFrameY;
					ispick = true;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		if (ispick) 
		{
			for (int y = startY; y <= endY; ++y)
			{
				for (int x = startX; x <= endX; ++x)
				{
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

}

void mapTool::setUp()
{
	_catalog = GRASS;

	_currentTile.terrain = TR_NONE;
	_currentTile.terrainFrameX = 0;
	_currentTile.terrainFrameY = 0;

	resizeX = to_string(_tileSet->getSizeX());
	resizeY = to_string(_tileSet->getSizeY());

	DRAW = RectMake(0, 0, CAMERAX, CAMERAY);
	leftCatalog = RectMakeCenter(TILESIZE * 20 + 150, 50, 25, 25);
	rightCatalog = RectMakeCenter(TILESIZE * 20 + 350, 50, 25, 25);
	save = RectMakeCenter(TILESIZE * 20 + 170, 500, 64, 64);
	load = RectMakeCenter(TILESIZE * 20 + 370, 500, 64, 64);
	SelectTileset = RectMakeCenter(TILESIZE * 20 -50 , 300, 300, 300);
	resize = RectMakeCenter(load.left, load.bottom + 100, 80, 30);
	sizeX = RectMakeCenter(resize.left-150, resize.top+15, 80,30);
	sizeY = RectMakeCenter(sizeX.left-150, sizeX.top+15 , 80, 30);

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