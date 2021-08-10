#include "stdafx.h"
#include "tileSet.h"

HRESULT tileSet::init()
{
	_tileX =  20;
	_tileY =  21;
	_tileBuffer = new image;
	_tileBuffer->init(BACKGROUNDX, BACKGROUNDY);
	setup();
	CAMERAMANAGER->setCamera(0, 0);
	return S_OK;
}

void tileSet::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() - 5);
		if (CAMERAMANAGER->getCameraLEFT() <= 0)
		{
			CAMERAMANAGER->setCameraX(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->setCameraCenterX(CAMERAMANAGER->getCameraCenterX() + 5);
		if (CAMERAMANAGER->getCameraRIGHT() >= _tileX * TILESIZE && _tileX*TILESIZE >= CAMERAX)
		{
			CAMERAMANAGER->setCameraX(_tileX*TILESIZE - CAMERAX);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() - 5);
		if (CAMERAMANAGER->getCameraTOP() <= 0)
		{
			CAMERAMANAGER->setCameraY(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->setCameraCenterY(CAMERAMANAGER->getCameraCenterY() + 5);
		if (CAMERAMANAGER->getCameraBOTTOM() >= _tileY * TILESIZE && _tileY*TILESIZE >= CAMERAY)
		{
			CAMERAMANAGER->setCameraY(_tileY*TILESIZE - CAMERAY);
		}
	}
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
			Rectangle(_tileBuffer->getMemDC(), _tiles[i][j].rc);
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
		}
	}
	CAMERAMANAGER->render(_tileBuffer, getMemDC());
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
	int qjadnlX = endx - startx;
	int qjadnlY = endy - starty;
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

	
	for (int y = 0; y <= qjadnlY; ++y)
	{
		for (int x = 0; x <= qjadnlX; ++x)
		{ 
			_tiles[presenty + y][presentx + x].terrain = _terrain;
			_tiles[presenty + y][presentx + x].terrainFrameX = startx + x;
			_tiles[presenty + y][presentx + x].terrainFrameY = starty + y;
		}
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
	delete[] tile;
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

	CloseHandle(file);
	delete[] tile;
}

