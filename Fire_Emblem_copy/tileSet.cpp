#include "stdafx.h"
#include "tileSet.h"

HRESULT tileSet::init()
{
	_tileX =  20;
	_tileY =  21;
	_tileBuffer = new image;
	_tileBuffer->init(BACKGROUNDX, BACKGROUNDY);
	setup();
	CAMERAMANAGER->setCamera(0, 20);
	return S_OK;
}

void tileSet::update()
{
	
}

void tileSet::release()
{

}

void tileSet::render()
{
	PatBlt(_tileBuffer->getMemDC(), 0, 0, BACKGROUNDX, BACKGROUNDY, WHITENESS);

	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			switch (_tiles[i][j].terrain)
			{
			case TR_NONE:
				break;
			case TR_GRASS:
				IMAGEMANAGER->frameRender("TR_Grass", _tileBuffer->getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case TR_KINGDOM:
				IMAGEMANAGER->frameRender("TR_KingDom", _tileBuffer->getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case TR_MOUNTIN:
				IMAGEMANAGER->frameRender("TR_MT", _tileBuffer->getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;

			}
			//if (KEYMANAGER->isToggleKey(VK_TAB))
			//{
			//	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			//	SelectObject(_tileBuffer->getMemDC(), myBrush);
			//	Rectangle(_tileBuffer->getMemDC(), _tiles[i][j].rc);
			//}
		}
	}
}

void tileSet::setup()
{
	for (int i = 0; i < _tileY; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < _tileX; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j*TILESIZE, i*TILESIZE, TILESIZE, TILESIZE);
			tile.terrain = TR_NONE;
			tile.terrainFrameX = 0;
			tile.terrainFrameY = 0;
			vTile.emplace_back(tile);
		}
		_tiles.emplace_back(vTile);
	}
}

void tileSet::drawTile(TERRAIN _terrain, int frameX, int frameY)
{
	for (int y = 0; y < _tileY; ++y)
	{
		for (int x = 0; x < _tileX; ++x)
		{
			POINT mouse;
			mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
			mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
			if (PtInRect(&_tiles[y][x].rc, mouse))
			{
				_tiles[y][x].terrain = _terrain;
				_tiles[y][x].terrainFrameX = frameX;
				_tiles[y][x].terrainFrameY = frameY;
			}
		}
	}
}

void tileSet::drawTile(TERRAIN _terrain, int startx, int starty, int endx, int endy)
{
	int presentx ,presenty;
	int rangeX = endx - startx;
	int rangeY = endy - starty;
	for (int y = 0; y < _tileY; ++y)
	{
		for (int x = 0; x < _tileX; ++x)
		{
			POINT mouse;
			mouse.x = _ptMouse.x + CAMERAMANAGER->getCameraLEFT();
			mouse.y = _ptMouse.y + CAMERAMANAGER->getCameraTOP();
			if (PtInRect(&_tiles[y][x].rc, mouse))
			{
				presentx = x;
				presenty = y;
			}
		}
	}

	
	for (int y = 0; y <= rangeY; ++y)
	{
		for (int x = 0; x <= rangeX; ++x)
		{ 
			_tiles[presenty + y][presentx + x].terrain = _terrain;
			_tiles[presenty + y][presentx + x].terrainFrameX = startx + x;
			_tiles[presenty + y][presentx + x].terrainFrameY = starty + y;	
			if (_terrain == TR_GRASS)
			{

				if ((startx + x == 3 || startx + x == 4)&&starty + y ==5)
				{
					_tiles[presenty + y][presentx + x].name = "풀";
					_tiles[presenty + y][presentx + x].def = 1;
					_tiles[presenty + y][presentx + x].avo = 20;
				}
				else if (startx + x == 5&& starty + y == 6)
				{
					_tiles[presenty + y][presentx + x].name = "숲";
					_tiles[presenty + y][presentx + x].def = 1;
					_tiles[presenty + y][presentx + x].avo = 20;
				}
				else
				{
					_tiles[presenty + y][presentx + x].name = "평지";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 0;
				}
			}
			else if (_terrain == TR_MOUNTIN)
			{
				_tiles[presenty + y][presentx + x].name = "산맥";
				_tiles[presenty + y][presentx + x].isMove = false;
				_tiles[presenty + y][presentx + x].def = 0;
				_tiles[presenty + y][presentx + x].avo = 0;
			}
			else if (_terrain == TR_KINGDOM)
			{
				if (startx + x == 1&& starty + y == 2)
				{
					_tiles[presenty + y][presentx + x].name = "마을";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
				else if (startx + x == 1 && starty + y == 5)
				{
					_tiles[presenty + y][presentx + x].name = "성문";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
				else if (startx + x == 0 && starty + y == 6)
				{
					_tiles[presenty + y][presentx + x].name = "민가";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
				else if (startx + x == 1 && starty + y ==6)
				{
					_tiles[presenty + y][presentx + x].name = "상점";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
				//새? def2 
				else if (startx + x == 2 && starty + y == 6)
				{
					_tiles[presenty + y][presentx + x].name = "요새";
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
				else
				{
					_tiles[presenty + y][presentx + x].name = "성벽";
					_tiles[presenty + y][presentx + x].isMove = false;
					_tiles[presenty + y][presentx + x].def = 0;
					_tiles[presenty + y][presentx + x].avo = 10;
				}
			}
		}
	}
}

void tileSet::resizeTile(int tilex, int tiley)
{
	if (_tileX > tilex)
	{
		for (int y = 0; y < _tileY; ++y)
		{
			for (int x = _tileX - 1; x >= tilex; --x)
			{
				_tiles[y].erase(_tiles[y].begin() + x);
			}
		}
		_tileX = tilex;
	}
	else
	{
		for (int y = 0; y < _tileY; ++y)
		{
			for (int x = _tileX; x < tilex; ++x)
			{
				tagTile tile;
				tile.rc = RectMake(x * TILESIZE, y * TILESIZE, TILESIZE, TILESIZE);
				tile.terrain = TR_NONE;
				tile.terrainFrameX = 0;
				tile.terrainFrameY = 0;
				tile.indexX = x;
				tile.indexY = y;
				_tiles[y].push_back(tile);
			}
		}
		_tileX = tilex;
	}


	if (_tileY > tiley)
	{
		for (int i = _tileY - 1; i >= tiley; --i)
		{
			_tiles[i].clear();
			_tiles.erase(_tiles.begin() + i);
		}
		_tileY = tiley;
	}
	else
	{
		for (int y = _tileY; y < tiley; ++y)
		{
			vector<tagTile> vTile;
			for (int x = 0; x < _tileX; ++x)
			{
				tagTile tile;
				tile.rc = RectMake(x*TILESIZE , y * TILESIZE, TILESIZE, TILESIZE);
				tile.terrain = TR_NONE;
				tile.terrainFrameX = 0;
				tile.terrainFrameY = 0;
				vTile.push_back(tile);
			}
			_tiles.push_back(vTile);
		}
		_tileY = tiley;
	}

}

void tileSet::save()
{
	//저장이요
	HANDLE file;
	DWORD write;
	tagTile *tile = new tagTile[_tileX * _tileY];
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			tile[i * _tileX + j] = _tiles[i][j];
		}
	}

	file = CreateFile("tile_save.map", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(tagTile) *_tileX * _tileY, &write, NULL);

	CloseHandle(file);
	//delete[] tile;
}

void tileSet::load()
{
	HANDLE file;
	DWORD read;
	tagTile *tile = new tagTile[_tileX * _tileY];
	file = CreateFile("tile_save.map", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tile, sizeof(tagTile) * _tileX * _tileY, &read, NULL);

	_tiles.clear();
	for (int i = 0; i < _tileY; i++)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < _tileX; j++)
		{
			vTile.push_back(tile[i * _tileX + j]);
		}
		_tiles.push_back(vTile);
	}

	_tileX = _tileX;
	_tileY = _tileY;


	for (int y = 0; y < _tileY; ++y)
	{
		for (int x = 0; x < _tileX; ++x)
		{ 
	
			if (_tiles[y][x].terrain == TR_GRASS)
			{

				if ((_tiles[y][x].terrainFrameX == 3 || _tiles[y][x].terrainFrameX == 4)&& _tiles[y][x].terrainFrameY ==5)
				{
					_tiles[y][x].name = "풀";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 1;
					_tiles[y][x].avo = 20;
				}
				else if (_tiles[y][x].terrainFrameX == 5&& _tiles[y][x].terrainFrameY == 6)
				{
					_tiles[y][x].name = "숲";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 1;
					_tiles[y][x].avo = 20;
				}
				else
				{
					_tiles[y][x].name = "평지";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 0;
				}
			}
			else if (_tiles[y][x].terrain == TR_MOUNTIN)
			{
				_tiles[y][x].name = "산맥";
				_tiles[y][x].isMove = false;
				_tiles[y][x].def = 0;
				_tiles[y][x].avo = 0;
			}
			else if (_tiles[y][x].terrain == TR_KINGDOM)
			{
				if (_tiles[y][x].terrainFrameX == 1&& _tiles[y][x].terrainFrameY == 2)
				{
					_tiles[y][x].name = "마을";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
				else if (_tiles[y][x].terrainFrameX == 1 && _tiles[y][x].terrainFrameY == 5)
				{
					_tiles[y][x].name = "성문";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
				else if (_tiles[y][x].terrainFrameX == 0 && _tiles[y][x].terrainFrameY == 6)
				{
					_tiles[y][x].name = "민가";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
				else if (_tiles[y][x].terrainFrameX == 1 && _tiles[y][x].terrainFrameY ==6)
				{
					_tiles[y][x].name = "상점";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
				//새? def2 
				else if (_tiles[y][x].terrainFrameX == 2 && _tiles[y][x].terrainFrameY == 6)
				{
					_tiles[y][x].name = "요새";
					_tiles[y][x].isMove = true;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
				else
				{
					_tiles[y][x].name = "성벽";
					_tiles[y][x].isMove = false;
					_tiles[y][x].def = 0;
					_tiles[y][x].avo = 10;
				}
			}
		}
	}



	CloseHandle(file);
	//delete[] tile;
}

