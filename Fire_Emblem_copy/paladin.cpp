#include "stdafx.h"
#include "paladin.h"

HRESULT paladin::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);

	_img = IMAGEMANAGER->findImage("�ȶ��Idle");

	return S_OK;
}

void paladin::update(int idx, int idy)
{
	unit::update(idx, idy);
	if (_astar->getStart() && _moveSelect)
	{
		_img = IMAGEMANAGER->findImage("�ȶ��move");
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used�ȶ��Idle");
	}
	else
	{
		_img = IMAGEMANAGER->findImage("�ȶ��Idle");

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

void paladin::release()
{
}

void paladin::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
