#include "stdafx.h"
#include "socialKnight.h"

HRESULT socialKnight::init(int idx, int idy, TYPE type)
{
	unit::init(idx, idy,type);
	switch (type)
	{
	case PLAYER:
		_img = IMAGEMANAGER->findImage("�Ҽȳ���ƮIdle");
		break;
	case ENEMY:
		_img = IMAGEMANAGER->findImage("enemy�Ҽȳ���ƮIdle");
		break;
	}
	return S_OK;

}

void socialKnight::update(int idx, int idy)
{
	unit::update(idx, idy);
	if (_astar->getStart())
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("�Ҽȳ���Ʈmove");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy�Ҽȳ���Ʈmove");
			break;
		}
	}
	else if (use)
	{
		_img = IMAGEMANAGER->findImage("used�Ҽȳ���ƮIdle");
	}
	else
	{
		switch (_type)
		{
		case PLAYER:
			_img = IMAGEMANAGER->findImage("�Ҽȳ���ƮIdle");
			break;
		case ENEMY:
			_img = IMAGEMANAGER->findImage("enemy�Ҽȳ���ƮIdle");
			break;
		}
	}
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

void socialKnight::release()
{
}

void socialKnight::render()
{
	_img->frameRender(_map->getMapDC(), stageX - (TILESIZE / 2), stageY - (TILESIZE), stageRenderX, stageRenderY);
}
