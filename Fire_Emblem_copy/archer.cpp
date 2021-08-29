#include "stdafx.h"
#include "archer.h"

HRESULT archer::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	
	_img = IMAGEMANAGER->findImage("��óIdle");

	return S_OK;
}

void archer::update(int idx, int idy)
{
	unit::update(idx, idy);
	if (_astar->getStart())
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("����move");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy����move");
			break;
		}
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used����Idle");
	}
	else
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("����Idle");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy����Idle");
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

void archer::release()
{
}

void archer::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
