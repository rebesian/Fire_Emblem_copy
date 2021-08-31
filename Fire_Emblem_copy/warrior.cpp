#include "stdafx.h"
#include "warrior.h"

HRESULT warrior::init(int idx, int idy ,TYPE type)
{
	unit::init(idx, idy , 5, type);
	name = "전사";
	switch (type)
	{
	case PLAYER:
		_img = IMAGEMANAGER->findImage("전사Idle");
		_hp = 20;
		attack = 10;
		critcal = 10;
		speed = 10;
		exp = 50;
		avoid = 55;
		break;
	case ENEMY:
		_img = IMAGEMANAGER->findImage("enemy전사Idle");
		_hp = 20;
		attack = 7;
		critcal = 10;
		speed = 10;
		exp = 50;
		avoid = 33;
		break;
	}

	return S_OK;
}

void warrior::update(int idx, int idy)
{
	unit::update(idx,idy);
	if (_astar->getStart())
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("전사move");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy전사move");
			break;
		}
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used전사Idle");
	}
	else 
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("전사Idle");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy전사Idle");
			break;
		}
	}

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
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
	if (battle)
	{
		char str[125];
		sprintf_s(str, "싸움!");
		TextOut(_map->getMapDC(), _rc.left, _rc.top, str, strlen(str));
	}
}
