#include "stdafx.h"
#include "transport.h"

HRESULT transport::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, 7,type);

	_img = IMAGEMANAGER->findImage("¼ö¼Û´ëIdle");
	
	return S_OK;
}

void transport::update(int idx, int idy)
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

void transport::release()
{
}

void transport::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
