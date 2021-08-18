#include "stdafx.h"
#include "warrior.h"

HRESULT warrior::init(int idx, int idy ,TYPE type)
{
	unit::init(idx, idy);
	switch (type)
	{
	case PLAYER:
		_img = IMAGEMANAGER->findImage("전사Idle");
		break;
	case ENEMY:
		_img = IMAGEMANAGER->findImage("enemy전사Idle");
		break;
	}
	stageX = _map->getRect(idx, idy).left;
	stageY = _map->getRect(idx, idy).top;
	stageRenderX = 0;
	stageRenderY = 0;
	return S_OK;
}

void warrior::update()
{
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
	_img->frameRender(CAMERAMANAGER->getCameraBuffer(), stageX, stageY, stageRenderX,stageRenderY);
}
