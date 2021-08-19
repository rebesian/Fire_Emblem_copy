#include "stdafx.h"
#include "mercenary.h"

HRESULT mercenary::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);

	_img = IMAGEMANAGER->findImage("¿ëº´Idle");

	stageX = _map->getRect(idx, idy).left;
	stageY = _map->getRect(idx, idy).top;

	stageRenderX = 0;
	stageRenderY = 0;

	return S_OK;
}

void mercenary::update()
{
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

void mercenary::release()
{
}

void mercenary::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
