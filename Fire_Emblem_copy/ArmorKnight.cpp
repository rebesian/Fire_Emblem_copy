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
