#include "stdafx.h"
#include "soider.h"

HRESULT soider::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, type);
	_img = IMAGEMANAGER->findImage("±ºÀÎIdle");
	return S_OK;
}

void soider::update(int idx, int idy)
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

void soider::release()
{
}

void soider::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
