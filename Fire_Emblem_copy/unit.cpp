#include "stdafx.h"
#include "unit.h"
#include "aStarTest.h"

HRESULT unit::init(int idx, int idy ,TYPE type)
{
	_astar = new aStarTest;
	_astar->setLinkMap(_map);
	_astar->init(idx, idy, 5, 1);
	_type = type;
	indexX = idx;
	indexY = idy;
	stageX = _map->getRect(idx, idy).left;
	stageY = _map->getRect(idx, idy).top;
	stageRenderX = 0;
	stageRenderY = 0;
	exp = 0;
	stageRenderCount = 0;
	battleRenderCount = 0;
	return S_OK;
}

void unit::update()
{

	if (_type == PLAYER)
	{

	}
	else if (_type  == ENEMY)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_astar->enemyEndSelect(indexX, indexY , 2, 10);
		}
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			_astar->callPathFinder();
		}
	}
	_astar->update();
	
}

void unit::release()
{

}

void unit::render()
{
	_astar->render();
}
