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

	battle = _moving = _pointing = _playerSelect = _moveSelect = false;
	stageRenderCount = 0;
	battleRenderCount = 0;
	return S_OK;
}

void unit::update(int idx, int idy)
{
	if (_type == PLAYER)
	{
		if (_pointing)
			stageRenderY = 1;
		else
			stageRenderY = 0;
		if (_playerSelect&& !_moveSelect)
		{
			if (!(idx == _astar->getTargetTileX() && idy == _astar->getTargetTileY())&&
				_astar->getAttribute(idx, idy) == "move")
			{
				_astar->EndSelect(idx, idy);
				_astar->callPathFinder();
			}
		}
		if (_moveSelect)
		{
			if (_astar->getStart())
			{
				if (_astar->getCloseListsize() > 0)
				{
					if (!_moving)
					{
						int pastX = indexX;
						int pastY = indexY;
						indexX = _astar->getClosebackX();
						indexY = _astar->getClosebackY();
						if (_astar->getAttribute(indexX, indexY) != "attack")
						{
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
							_moving = true;
						}
						else
						{
							indexX = pastX;
							indexY = pastY;
							_astar->clear();
						}
					}
					else
					{
						if (stageX == _rc.left  && stageY == _rc.top)
						{
							_moving = false;
							_astar->move(indexX, indexY);
						}
						else
						{
							switch (_dir)
							{
							case LEFT:
								stageX -= 5;
								if (stageX < _rc.left) stageX = _rc.left;
								stageRenderY = 0;
								break;
							case RIGHT:
								stageX += 5;
								if (stageX > _rc.left) stageX = _rc.left;
								stageRenderY = 1;
								break;
							case UP:
								stageY -= 5;
								if (stageY < _rc.top) stageY = _rc.top;
								stageRenderY = 3;
								break;
							case DOWN:
								stageY += 5;
								if (stageY > _rc.top) stageY = _rc.top;
								stageRenderY = 2;
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
			else
			{
				if (!_moving)
				{
					int pastX = indexX;
					int pastY = indexY;
					indexX = _astar->getTargetTileX();
					indexY = _astar->getTargetTileY();
					if (_astar->getAttribute(indexX, indexY) != "attack")
					{
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
						_moving = true;
					}
					else
					{
						indexX = pastX;
						indexY = pastY;
					}
				}
				else
				{
					if (stageX == _rc.left  && stageY == _rc.top)
					{
						_moving = false;
						_astar->move(indexX, indexY);
						//_astar->setMoveTile(indexX, indexY);
						_moveSelect = false;
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
							if (stageY > _rc.top) stageY = _rc.top;
							break;
						}
					}
				}
			}
		}
		else
		{
			stageRenderY = 0;
		}
	}
	else if (_type  == ENEMY)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_astar->EndSelect(2, 10);
		}
		if (KEYMANAGER->isOnceKeyDown('V'))
		{
			_astar->callPathFinder();
		}
		if (_astar->getStart())
		{
			if (_astar->getCloseListsize() > 0)
			{
				if (!_moving)
				{
					int pastX = indexX;
					int pastY = indexY;
					indexX = _astar->getClosebackX();
					indexY = _astar->getClosebackY();
					if (_astar->getAttribute(indexX, indexY) != "attack")
					{
						if (pastX == indexX)
						{
							if (pastY > indexY)
							{
								_dir = UP;
								stageRenderY = 3;
							}
							else if (pastY < indexY)
							{
								_dir = DOWN;
								stageRenderY = 2;
							}
						}
						else if (pastY == indexY)
						{
							if (pastX > indexX)
							{
								_dir = LEFT;
								stageRenderY = 0;
							}
							else
							{
								_dir = RIGHT;
								stageRenderY = 1;
							}
						}
						_rc = _map->getRect(indexX, indexY);
						_moving = true;
					}
					else
					{
						indexX = pastX;
						indexY = pastY;
						_astar->clear();
					}
				}
				else
				{
					if (stageX == _rc.left  && stageY == _rc.top)
					{
						_moving = false;
						_astar->move(indexX, indexY);
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
							if (stageY > _rc.top) stageY = _rc.top;
							break;
						}
					}
				}
			}
			else
			{
				_astar->setStart(false);
				if (indexX - 1 == _astar->getTargetTileX() ||
					indexX + 1 == _astar->getTargetTileX() ||
					indexY - 1 == _astar->getTargetTileY() ||
					indexY + 1 == _astar->getTargetTileY())
					battle = true;
				_astar->setMoveTile(indexX, indexY);
				stageRenderY = 0;
			}
		}
	}
	_astar->update(_playerSelect);
	
}

void unit::release()
{

}

void unit::render()
{

	_astar->render();

}
