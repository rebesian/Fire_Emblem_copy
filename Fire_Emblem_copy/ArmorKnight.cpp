#include "stdafx.h"
#include "ArmorKnight.h"

HRESULT ArmorKnight::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	
	_img = IMAGEMANAGER->findImage("아머나이트Idle");

	return S_OK;
}

void ArmorKnight::update(int idx, int idy)
{
	unit::update(idx, idy);
	if (_astar->getStart())
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("아머나이트move");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy아머나이트move");
			break;
		}
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used아머나이트Idle");
	}
	else
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("아머나이트Idle");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy아머나이트Idle");
			break;
		}
	}
	stageRenderCount++;
	if (stageRenderCount % 7 == 0)
	{
		if (stageRenderX == 2)
		{
			if (stageRenderCount > 20)
				stageRenderX = 0;
		}
		else
		{
			stageRenderX++;
			stageRenderCount = 0;
		}
	}
}

void ArmorKnight::release()
{
}

void ArmorKnight::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
