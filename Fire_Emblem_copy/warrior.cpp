#include "stdafx.h"
#include "warrior.h"

HRESULT warrior::init(int idx, int idy ,TYPE type)
{
	unit::init(idx, idy , type);
	switch (type)
	{
	case PLAYER:
		_img = IMAGEMANAGER->findImage("전사Idle");
		break;
	case ENEMY:
		_img = IMAGEMANAGER->findImage("enemy전사Idle");
		break;
	}

	return S_OK;
}

void warrior::update()
{
	unit::update();
	stageRenderCount++;
	if (stageRenderCount % 7 == 0)
	{
		stageRenderX++;
		if (stageRenderX == 3)
		{
			stageRenderX = 0;
		}
		else
		{
			stageRenderCount = 0;
		}
	}
}

void warrior::release()
{

}

void warrior::render()
{
	unit::render();
	if (!_render)
	{
		_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
	}
}
