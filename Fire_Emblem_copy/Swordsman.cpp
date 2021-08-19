#include "stdafx.h"
#include "Swordsman.h"

HRESULT Swordsman::init(int idx, int idy,TYPE type)
{
	unit::init(idx, idy,type);

	_img = IMAGEMANAGER->findImage("°Ë»çIdle");
	
	stageX = _map->getRect(idx, idy).left;
	stageY = _map->getRect(idx, idy).top;
	stageRenderX = 0;
	stageRenderY = 0;
	return S_OK;
}

void Swordsman::update()
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

void Swordsman::release()
{
}

void Swordsman::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
