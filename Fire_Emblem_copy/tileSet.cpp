#include "stdafx.h"
#include "tileSet.h"

HRESULT tileSet::init()
{
	_tileX = 20;
	_tileY = 20; 
	
	setup();

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
	for (int i = 0; i < _tileY; ++i)
	{
		for (int j = 0; j < _tileX; ++j)
		{
			Rectangle(getMemDC(), _tiles[i][j].rc);
			switch (_tiles[i][j].terrain)
			{
			case TR_NONE:
				break;
			case TR_GRASS:
				IMAGEMANAGER->frameRender("TR_Grass", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case TR_KINGDOM:
				IMAGEMANAGER->frameRender("TR_KingDom", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case TR_MOUNTIN:
				IMAGEMANAGER->frameRender("TR_MT", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top,
					_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;

			}
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
			if (PtInRect(&_tiles[y][x].rc, _ptMouse))
			{
				_tiles[y][x].terrain = _terrain;
				_tiles[y][x].terrainFrameX = frameX;
				_tiles[y][x].terrainFrameY = frameY;
			}
		}
	}
}

