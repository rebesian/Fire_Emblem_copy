#include "stdafx.h"
#include "prist.h"

HRESULT prist::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	
	_img = IMAGEMANAGER->findImage("프리스트Idle");

	return S_OK;
}

void prist::update()
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

void prist::release()
{
}

void prist::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
