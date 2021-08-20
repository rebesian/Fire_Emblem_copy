#include "stdafx.h"
#include "archer.h"

HRESULT archer::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	
	_img = IMAGEMANAGER->findImage("¾ÆÃ³Idle");

	return S_OK;
}

void archer::update()
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

void archer::release()
{
}

void archer::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
