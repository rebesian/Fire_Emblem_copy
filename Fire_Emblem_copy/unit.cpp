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
	_rc = _map->getRect(idx, idy);
	stageX = _rc.left;
	stageY = _rc.top;
	stageRenderX = 0;
	stageRenderY = 0;
	exp = 0;

	_render = false;
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
		if (_astar->getStart())
		{
			if (_astar->getCloseListsize() > 0)
			{
				if (!_render)
				{
					int pastX = indexX;
					int pastY = indexY;
					indexX = _astar->getClosebackX();
					indexY = _astar->getClosebackY();

					if (pastX == indexX)
					{
						if (pastY > indexY)
						{
							_dir = UP;
						}
						else if (pastY < indexY)
						{
							_dir = DOWN;
						}
					}
					else if (pastY == indexY)
					{
						if (pastX > indexX)
						{
							_dir = LEFT;
						}
						else
						{
							_dir = RIGHT;
						}
					}


					_rc = _map->getRect(indexX, indexY);
					_astar->move(indexX, indexY);
					_render = true;
					_img = IMAGEMANAGER->findImage("");
				}
				else
				{
					if (stageX == _rc.left  && stageY == _rc.top)
					{
						_render = false;
					}
					else
					{
						switch (_dir)
						{
						case LEFT:
							stageX -= 5;
							if (stageX < _rc.left) stageX = _rc.left;
							break;
						case RIGHT:
							stageX += 5;
							if (stageX > _rc.left) stageX = _rc.left;
							break;
						case UP:
							stageY -= 5;
							if (stageY < _rc.top) stageY = _rc.top;
							break;
						case DOWN:
							stageY += 5;
							if (stageX < _rc.top) stageX = _rc.top;
							break;
						}
					}
				}
			}
			else
			{
				_astar->setStart(false);
			}
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
