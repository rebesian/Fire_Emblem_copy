#include "stdafx.h"
#include "unit.h"
#include "aStarTest.h"

HRESULT unit::init(int idx, int idy , int moveRange, TYPE type)
{
	_astar = new aStarTest;
	_astar->setLinkMap(_map);
	_astar->init(idx, idy, moveRange, 1);
	_type = type;
	indexX = idx;
	indexY = idy;
	_rc = _map->getRect(idx, idy);
	stageX = _rc.left;
	stageY = _rc.top;
	stageRenderX = 0;
	stageRenderY = 0;
	exp = 0;
	if (_type == PLAYER)
	{
		_map->setIsPlayer(idx, idy, true);
	}
	else if(_type == ENEMY)
	{
		_map->setIsEnemy(idx, idy, true);
	}
	battle = _render =_moving = _pointing = _playerSelect = _moveSelect = false;
	stageRenderCount = 0;
	battleRenderCount = 0;
	return S_OK;
}

void unit::update(int idx, int idy)
{
	if (_type == PLAYER)
	{
		if (_pointing && !_moveSelect)
			stageRenderY = 1;
		else if(!_pointing && !_moveSelect)
			stageRenderY = 0;
		if (_playerSelect)
		{
			if (!(idx == _astar->getTargetTileX() && idy == _astar->getTargetTileY())&&
				_astar->getAttribute(idx, idy) == "move")
			{
				_map->setIsPlayer(indexX, indexY, false);
				_astar->EndSelect(idx, idy);
				_astar->callPathFinder();
			}
			if (!_render)
			{
				_astar->setMoveTile(idx, idy);
				_render = true;
			}
		}
		if (_moveSelect)
		{
			_playerSelect = false;
			if (_render) _render = false;
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
						_map->setIsPlayer(indexX, indexY, true);
						_astar->setAttackTile(indexX, indexY);

						//여기가 적 탐색하는곳
						if (_astar->getEnemysize()>0)
						{
							_attackSelect = true;

						}
						else
						{
							use = true;
						}
						_moveSelect = false;
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
		}
		if (_attackSelect)
		{
			if (!_render) _render = true;
 			
		}
	}
	else if (_type == ENEMY)
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
				_map->setIsEnemy(indexX, indexY, true);
				if (indexX - 1 == _astar->getTargetTileX() ||
					indexX + 1 == _astar->getTargetTileX() ||
					indexY - 1 == _astar->getTargetTileY() ||
					indexY + 1 == _astar->getTargetTileY())
					battle = true;
				_astar->setMoveTile(indexX, indexY);
				use = true;
				stageRenderY = 0;
			}
		}
	}
	if(use)
	{
		_render = false;
	}
	_astar->update(_render);

}

void unit::release()
{

}

void unit::render()
{

	_astar->render();

}

void unit::targetOn(int idx, int idy)
{
	_map->setIsEnemy(indexX, indexY, false);
	_astar->EndSelect(idx, idy);
	_astar->callPathFinder();

}
