#include "stdafx.h"
#include "soider.h"

HRESULT soider::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, 5,type);
	_img = IMAGEMANAGER->findImage("군인Idle");
	name = "군인";
	_hp = 20;
	attack = 7;
	critcal = 10;
	speed = 10;
	exp = 50;
	avoid = 33;
	return S_OK;
}

void soider::update(int idx, int idy)
{
	unit::update(idx, idy);
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
	unit::render();
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
