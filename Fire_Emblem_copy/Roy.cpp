#include "stdafx.h"
#include "Roy.h"

HRESULT Roy::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy, 5,type);
	name = "로이";
	_hp = 20;
	attack = 10;
	critcal = 10;
	speed = 10;
	exp = 50;
	avoid = 55;
	_img = IMAGEMANAGER->findImage("로이Idle");
	return S_OK;
}

void Roy::update(int idx, int idy)
{

	unit::update(idx, idy);
	if (_astar->getStart()&&_moveSelect)
	{
		_img = IMAGEMANAGER->findImage("로이move");
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used로이Idle");
	}
	else
	{
		_img = IMAGEMANAGER->findImage("로이Idle");
	
	}
	stageRenderCount++;
	
	if (stageRenderCount % 7 == 0)
	{
		if (stageRenderX == 2)
		{
			if(stageRenderCount>20)
			stageRenderX = 0;
		}
		else
		{
			stageRenderX++;
			stageRenderCount = 0;
		}
	}
}

void Roy::release()
{

}

void Roy::render()
{
	unit::render();
	_img->frameRender(_map->getMapDC(), stageX-(TILESIZE/2), stageY-(TILESIZE), stageRenderX, stageRenderY);


}
