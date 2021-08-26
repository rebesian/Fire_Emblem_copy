#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init(int playerX, int playerY, int moveRange , int attackRange)
{
	_count = _moveTileCount = 0;
	_start = _render = false;
	damage = false;
	_totalRange = moveRange + attackRange;
	_moveRange = moveRange;
	_attackRange = attackRange;
	setTile(playerX, playerY);
	time = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void aStarTest::release()
{

}

void aStarTest::update(bool render)
{
	_render = render;
	if (_render)
	{
		for (int y = 0; y < _vTotalList.size(); ++y)
		{
			for (int x = 0; x < _vTotalList[y].size(); ++x)
			{
				if(_vTotalList[y][x]->getAttribute()!="none")
				_vTotalList[y][x]->update();
			}
		}
	}

}

void aStarTest::render()
{				
	char str[12];
	sprintf_s(str, "타겟여기><");

	if (_render)
	{
		for (int y = 0; y < _vTotalList.size(); ++y)					
		{
			for (int x = 0; x < _vTotalList[y].size(); ++x)
			{
				//HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				//SelectObject(_map->getMapDC(), myBrush);
				//RECT temp = _vTotalList[y][x]->getRect();
				//Rectangle(_map->getMapDC(), temp);
				if(_vTotalList[y][x]->getAttribute()!="none")
				{ 
					HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
					SelectObject(_map->getMapDC(), myBrush);
					RECT temp = _vTotalList[y][x]->getRect();
					Rectangle(_map->getMapDC(), temp);
					_vTotalList[y][x]->render();
				}
			
			}
		}
		route();
	}

}

//타일 셋팅 함수
void aStarTest::setTile(int playerX, int playerY)
{
	_vTotalList.clear();
	_moveTileCount = 0;
	_startTile = new tile;
	_startTile->setLinkMap(_map);
	_startTile->init(playerX, playerY);
	_startTile->setAttribute("move");

	_endTile = new tile;
	_endTile->setLinkMap(_map);
	_endTile->init(playerX, playerY);
	_endTile->setAttribute("move");
	_endTile->setIsEnd(true);


	_currentTile = _startTile;
	

	for (int y = 0 ; y <_map->getSizeY(); ++y)
	{
		vector<tile*> TotalList;
		for (int x =0 ; x <_map->getSizeX(); ++x)
		{
			if (x == playerX && playerY == y)
			{
				TotalList.push_back(_startTile);
			
				continue;
			}
			tile* node = new tile;
			node->setLinkMap(_map);
			node->init(x, y);
			TotalList.push_back(node);
		}
		_vTotalList.push_back(TotalList);
	}

	setMoveTile(playerX, playerY);
}

//갈수있는길추가함수
vector<tile*> aStarTest::addOpenList(tile * currentTile)
{

	int startX = currentTile->getIdX();
	int startY = currentTile->getIdY();

	for (int i = 0; i < 4; ++i)
	{
		if (i == 0 || i == 2)
		{
			if (startX - 1 + i < 0 || startX - 1 + i >= _map->getSizeX()) continue;
			tile* node = _vTotalList[startY][startX-1+i];
			//예외처리
			if (!node->getIsOpen()) continue;

			//현재 타일 계속 갱신해준다.
			node->setParentNode(_currentTile);
			//node->setparentNumber(_currentTile->getparentNumber() + 1);
			//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			////현재 노드가 끝노드가아니면 색칠해준다
			//if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

			//이미 체크된애는 건너뛴다
			if (!addObj) continue;
			//갈수있는 길은 백터에 저장된다
			_vOpenList.push_back(node);

		}
		if (i == 1 || i == 3)
		{
			if (startY - 2 + i < 0 || startY - 2 + i >= _map->getSizeY()) continue;
			tile* node = _vTotalList[startY-2+i][startX];
			//예외처리
			if (!node->getIsOpen()) continue;

			//현재 타일 계속 갱신해준다.
			node->setParentNode(_currentTile);
			//node->setparentNumber(_currentTile->getparentNumber() + 1);

			//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			//현재 노드가 끝노드가아니면 색칠해준다
			//if (node->getAttribute() != "player");

			//이미 체크된애는 건너뛴다
			if (!addObj) continue;
			//갈수있는 길은 백터에 저장된다
			_vOpenList.push_back(node);

		}

	}
	
	return _vOpenList;
}

//길 찾는 함수
void aStarTest::pathFinder(tile * currentTile)
{
	//비교용 최종경로비용설정
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	//오픈리스트 백터안에서, 가장빠른경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H값연산 (현재지점에서 끝지점까지)
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) + abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//현재 start기준 타일중점
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//오픈리스트의 해당 타일중점
		POINT center2 = _vOpenList[i]->getCenter();

		//G값연산 (처음지점에서 현재지점까지)
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y));

		//F = G + H 총값더하기sv
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getFromCost() + _vOpenList[i]->getToGoal());
		//그렇게 뽑아낸 총 경로 비용들을 임의의 경로비용과 연산하여 가장 작은값을 계속 뽑아낸다.
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			//그 작은타일값을 넣는다
			tempTile = _vOpenList[i];
		}

		//같은값인거 체크용
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			//이미 빠른길이라고 지정됬다면?
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		//재확인안하려고 Openfalse
		_vOpenList[i]->setIsOpen(false);
		//중복체크가아니라면
		if (!addObj) continue;
		//중복이안됬다면 새로 넣어준다
		_vOpenList.push_back(tempTile);
	}


	if (tempTile == nullptr)
	{
		return;
	}
	else if (tempTile->getIsEnd())
	{
		//최단경로를 색칠해줘라
		while (_currentTile != _startTile)
		{
			_vCloseList.emplace_back(_currentTile);
			//_vOpenList.clear();
			_start = true;
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}

	//최단경로를 넣어놧으면
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//그 오픈리스트에서 삭제해줍시다
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
	
	pathFinder(_currentTile);

}

void aStarTest::EndSelect(int endIndexX, int endIndexY)
{
	if(endIndexX == _startTile->getIdX() && endIndexY == _startTile->getIdY())
	{
		
	}
	else
	{
		RECT rc;
		tile* node = new tile;
		node->setLinkMap(_map);
		node->init(_endTile->getIdX(), _endTile->getIdY());
		node->setAttribute("move");
		_endTile->setIdX(endIndexX);
		_endTile->setIdY(endIndexY);
		rc = _map->getRect(_endTile->getIdX(), _endTile->getIdY());
		_endTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
		_endTile->setRect(rc);
		_vTotalList[node->getIdY()].erase(_vTotalList[node->getIdY()].begin() + node->getIdX());
		_vTotalList[node->getIdY()].insert(_vTotalList[node->getIdY()].begin() + node->getIdX(), node);
		_vTotalList[endIndexY].erase(_vTotalList[endIndexY].begin() + endIndexX);
		_vTotalList[endIndexY].insert(_vTotalList[endIndexY].begin() + endIndexX, _endTile);

	}
}

void aStarTest::setMoveTile(int playerX , int playerY)
{

	for (int y = 0; y < _vTotalList.size(); ++y)
	{
		for (int x = 0; x < _vTotalList[y].size(); ++x)
		{
			_vTotalList[y][x]->setRenderCounter();
			if (x == playerX && y == playerY)
			{
				_vTotalList[playerY][playerX]->setAttribute("move");
				_moveTileCount++;
				_vTotalList[y][x]->setIsOpen(true);
				continue;
			}
			_vTotalList[y][x]->setIsOpen(true);
			_vTotalList[y][x]->setAttribute("none");
		}
	}


	_movecount = _moveRange;

	//상 Move넣기
	for (int i = 1; i <= _moveRange; ++i)
	{
		if (playerY - i < 0) break;
		if (!_map->getMove(playerX, playerY - i)) _movecount = 0;
		if (_movecount > 0)
		{
			_vTotalList[playerY - i][playerX]->setAttribute("move");
			_moveTileCount++;
			--_movecount;
		}
		else
			break;

	}

	_movecount = _moveRange;


	//하 Move넣기
	for (int i = 1; i <= _moveRange; ++i)
	{
		if (playerY + i > _map->getSizeY()) break;
		if (!_map->getMove(playerX, playerY + i)) _movecount = 0;
		if (_movecount > 0)
		{
			_vTotalList[playerY + i][playerX]->setAttribute("move");
			_moveTileCount++;
			_movecount--;
		}
		else
			break;
	}

	_movecount = _moveRange;


	//좌 move넣기
	for (int i = 1; i <= _moveRange; ++i)
	{
		if (playerX - i < 0) break;
		if (!_map->getMove(playerX - i, playerY)) _movecount = 0;
		if (_movecount > 0)
		{
			_vTotalList[playerY][playerX - i]->setAttribute("move");
			_moveTileCount++;
			--_movecount;
		}
		else
			break;

	}

	_movecount = _moveRange;

	//우 move넣기			
	for (int i = 1; i <= _moveRange; ++i)
	{
		if (playerX + i >= _map->getSizeX()) break;
		if (!_map->getMove(playerX + i, playerY)) _movecount = 0;
		if (_movecount > 0)
		{
			_vTotalList[playerY][playerX + i]->setAttribute("move");
			_moveTileCount++;
			--_movecount;
		}
		else
			break;
	}

	//1사분면 move넣기
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY - y < 0)
			break;
		_movecount -= y;
		for (int x = 1; x <= _moveRange - y; ++x)
		{
			if (playerX + x >= _map->getSizeX())
				break;
			if (!_map->getMove(playerX + x, playerY - y)) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerY - y][playerX + x]->setAttribute("move");
				_moveTileCount++;
				--_movecount;
			}
			else
				break;

		}
	}
	//2사분면 move넣기
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY - y < 0)
			break;
		_movecount -= y;
		for (int x = 1; x <= _moveRange - y; ++x)
		{
			if (playerX - x < 0)
				break;
			if (!_map->getMove(playerX - x, playerY - y)) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerY - y][playerX - x]->setAttribute("move");
				_moveTileCount++;
				--_movecount;
			}
			else
				break;

		}
	}

	//3사분면 move넣기
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY + y >= _map->getSizeY())
			break;
		_movecount -= y;
		for (int x = 1; x <= _moveRange; ++x)
		{
			if (playerX - x < 0)
				break;
			if (!_map->getMove(playerX - x, playerY + y)) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerY + y][playerX - x]->setAttribute("move");
				_moveTileCount++;
				--_movecount;
			}
			else
				break;
		}
	}

	//4사분면 move넣기
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY + y >= _map->getSizeY())
			break;
		_movecount -= y;
		for (int x = 1; x <=_moveRange - y; ++x)
		{
			if (playerX + x >= _map->getSizeX())
				break;
			if (!_map->getMove(playerX + x, playerY + y)) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerY + y][playerX + x]->setAttribute("move");
				_moveTileCount++;
				--_movecount;
			}
			else
				break;
		}
	}


	//attack넣기
	for (int y = 0; y < _vTotalList.size(); ++y)
	{
		if (_moveTileCount < 0)
			break;
		for (int x = 0; x < _vTotalList[y].size(); ++x)
		{

			if (_moveTileCount < 0)
				break;
			if (_vTotalList[y][x]->getAttribute() == "move")
			{
				int z = _attackRange;
				//왼쪽
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j <= abs(i+z); ++j)
					{
						if (y + i <0 || y + i >= _map->getSizeY() || x + j >=_map->getSizeX()) continue;
						if (_vTotalList[y + i][x + j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x + j]->setAttribute("attack");
							_vTotalList[y + i][x + j]->setIsOpen(false);
						}

					}
					if (i >= 0)
						z = -_attackRange;
				}

				z = _attackRange;
				//오른쪽
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j <= abs(i + z); ++j)
					{
						if ( y+i <0|| y + i >= _map->getSizeY() || x - j < 0) continue;
						if (_vTotalList[y + i][x - j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x - j]->setAttribute("attack");
							_vTotalList[y + i][x - j]->setIsOpen(false);
						}

					}
					if (i >=0)
						z = -_attackRange;
				}
				--_moveTileCount;
			}
		}
	}

}

void aStarTest::setAttackTile(int playerX, int playerY)
{
	for (int y = 0; y < _vTotalList.size(); ++y)
	{
		for (int x = 0; x < _vTotalList[y].size(); ++x)
		{
			_vTotalList[y][x]->setAttribute("none");
		}
	}


	_vEnemy.clear();
		
	int z = _attackRange;
	//왼쪽
	for (int i = -_attackRange; i <= _attackRange; ++i)
	{
		for (int j = 0; j <= abs(i + z); ++j)
		{
			if (playerY + i < 0 || playerY + i >= _map->getSizeY() || playerX + j >= _map->getSizeX()) continue;
			if (playerY + i == playerY && playerX + j == playerX) continue;
			if (_vTotalList[playerY + i][playerX + j]->getAttribute() == "none")
			{
				_vTotalList[playerY + i][playerX + j]->setAttribute("attack");
				if (_map->getIsEnemy(playerX + j, playerY + i))
				{
					_vEnemy.push_back(_vTotalList[playerY + i][playerX + j]);
				}
			}

		}
		if (i >= 0)
			z = -_attackRange;
	}

	z = _attackRange;
	//오른쪽
	for (int i = -_attackRange; i <= _attackRange; ++i)
	{
		for (int j = 0; j <= abs(i + z); ++j)
		{
			if (playerY + i < 0 || playerY + i >= _map->getSizeY() || playerX - j < 0) continue;
			if (playerY + i == playerY && playerX + j == playerX) continue;
			if (_vTotalList[playerY + i][playerX - j]->getAttribute() == "none")
			{
				_vTotalList[playerY + i][playerX - j]->setAttribute("attack");
				if (_map->getIsEnemy(playerX + j, playerY + i))
				{
					bool istrue = false;
					for (int q = 0; q < _vEnemy.size(); ++q)
					{
						if (_vEnemy[q]->getIdX() == playerX + j
							|| _vEnemy[q]->getIdY() == playerY + i)
							istrue = true;

					}
					if(!istrue)
						_vEnemy.push_back(_vTotalList[playerY + i][playerX + j]);
				}
			}
		}
		if (i >= 0)
			z = -_attackRange;
	}
	
	
	
	
}

void aStarTest::move(int X, int Y)
{
	RECT rc;
	tile* node = new tile;
	node->setLinkMap(_map);
	node->init(_startTile->getIdX(), _startTile->getIdY());
	node->setAttribute("move");
	_startTile->setIdX(X);
	_startTile->setIdY(Y);
	rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	_startTile->setRect(rc);
	_vTotalList[node->getIdY()].erase(_vTotalList[node->getIdY()].begin() + node->getIdX());
	_vTotalList[node->getIdY()].insert(_vTotalList[node->getIdY()].begin() + node->getIdX(), node);
	_vTotalList[Y].erase(_vTotalList[Y].begin() + X);
	_vTotalList[Y].insert(_vTotalList[Y].begin() + X, _startTile);
	if (_vCloseList.size() > 0)
	{
		_vCloseList.erase(_vCloseList.end() - 1);
	}

}



void aStarTest::callPathFinder()
{
	for (int i = 0; i < _vCloseList.size(); ++i)
	{
		_vTotalList[_vCloseList[i]->getIdY()][_vCloseList[i]->getIdX()]->setIsOpen(true);
	}
	for (int i = 0; i < _vOpenList.size(); ++i)
	{
		_vTotalList[_vOpenList[i]->getIdY()][_vOpenList[i]->getIdX()]->setIsOpen(true);
	}
	
	_vCloseList.clear();
	_vOpenList.clear();
	pathFinder(_startTile);
}

void aStarTest::route()
{
	if (_vCloseList.size() > 0)
	{
		if (_vCloseList.size() > 2)
		{
			if (_startTile->getIdX() == _vCloseList.back()->getIdX())
			{
				if (_startTile->getIdY() > _vCloseList.back()->getIdY())
				{
					_startTile->routeRender(2, 0);
					if (_vCloseList.back()->getIdX() == _vCloseList[_vCloseList.size() - 2]->getIdX())
					{
						_vCloseList.back()->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList.back()->getIdX() > _vCloseList[_vCloseList.size() - 2]->getIdX())
						{
							_vCloseList.back()->routeRender(0, 2);
						}
						else
						{
							_vCloseList.back()->routeRender(3, 2);
						}
					}
				}
				else
				{
					_startTile->routeRender(3, 0);
					if (_vCloseList.back()->getIdX() == _vCloseList[_vCloseList.size() - 2]->getIdX())
					{
						_vCloseList.back()->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList.back()->getIdX() > _vCloseList[_vCloseList.size() - 2]->getIdX())
						{
							_vCloseList.back()->routeRender(2, 2);
						}
						else
						{
							_vCloseList.back()->routeRender(1, 2);
						}
					}
				}
			}
			else if (_startTile->getIdY() == _vCloseList.back()->getIdY())
			{
				if (_startTile->getIdX() > _vCloseList.back()->getIdX())
				{
					_startTile->routeRender(0, 0);
					if (_vCloseList.back()->getIdY() == _vCloseList[_vCloseList.size() - 2]->getIdY())
					{
						_vCloseList.back()->routeRender(0, 1);
					}
					else
					{
						if (_vCloseList.back()->getIdY() > _vCloseList[_vCloseList.size() - 2]->getIdY())
						{
							_vCloseList.back()->routeRender(1, 2);
						}
						else
						{
							_vCloseList.back()->routeRender(3, 2);
						}
					}
				}
				else
				{
					_startTile->routeRender(1, 0);
					if (_vCloseList.back()->getIdY() == _vCloseList[_vCloseList.size() - 2]->getIdY())
					{
						_vCloseList.back()->routeRender(1, 1);
					}
					else
					{
						if (_vCloseList.back()->getIdY() > _vCloseList[_vCloseList.size() - 2]->getIdY())
						{
							_vCloseList.back()->routeRender(0, 2);
						}
						else
						{
							_vCloseList.back()->routeRender(2, 2);
						}
					}
				}
			}
			for (int i = 1; i < _vCloseList.size() - 1; ++i)
			{
				if (_vCloseList[i - 1]->getIdX() == _vCloseList[i]->getIdX())
				{
					if (_vCloseList[i - 1]->getIdY() > _vCloseList[i]->getIdY())
					{
						if (_vCloseList[i]->getIdX() == _vCloseList[i + 1]->getIdX())
						{
							routeY = 1;
							routeX = 2;
						}
						else
						{
							if (_vCloseList[i]->getIdX() > _vCloseList[i + 1]->getIdX())
							{
								routeY = 2;
								routeX = 2;
							}
							else
							{
								routeY = 2;
								routeX = 3;
							}
						}
					}
					else
					{
						if (_vCloseList[i]->getIdX() == _vCloseList[i + 1]->getIdX())
						{
							routeY = 1;
							routeX = 2;
						}
						else
						{
							if (_vCloseList[i]->getIdX() > _vCloseList[i + 1]->getIdX())
							{
								routeY = 2;
								routeX = 0;
							}
							else
							{
								routeY = 2;
								routeX = 1;
							}
						}
					}

				}
				else if (_vCloseList[i - 1]->getIdY() == _vCloseList[i]->getIdY())
				{
					if (_vCloseList[i - 1]->getIdX() < _vCloseList[i]->getIdX())
					{
						if (_vCloseList[i]->getIdY() == _vCloseList[i + 1]->getIdY())
						{
							routeY = 1;
							routeX = 1;
						}
						else
						{
							if (_vCloseList[i]->getIdY() > _vCloseList[i + 1]->getIdY())
							{
								routeY = 2;
								routeX = 0;
							}
							else
							{
								routeY = 2;
								routeX = 2;
							}
						}
					}
					else
					{
						if (_vCloseList[i]->getIdY() == _vCloseList[i + 1]->getIdY())
						{
							routeY = 1;
							routeX = 1;
						}
						else
						{
							if (_vCloseList[i]->getIdY() > _vCloseList[i + 1]->getIdY())
							{
								routeY = 2;
								routeX = 1;
							}
							else
							{
								routeY = 2;
								routeX = 3;
							}
						}
					}
				}
				_vCloseList[i]->routeRender(routeX, routeY);
			}
			if (_endTile->getIdX() == _vCloseList.front()->getIdX())
			{
				if (_vCloseList.front()->getIdY() > _endTile->getIdY())
				{
					_endTile->routeRender(2, 3);
					if (_vCloseList.front()->getIdX() == _vCloseList[1]->getIdX())
					{
						_vCloseList.front()->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList.front()->getIdX() > _vCloseList[1]->getIdX())
						{
							_vCloseList.front()->routeRender(0, 2);
						}
						else
						{
							_vCloseList.front()->routeRender(1, 2);
						}
					}
				}
				else
				{
					_endTile->routeRender(3, 3);
					if (_vCloseList.front()->getIdX() == _vCloseList[1]->getIdX())
					{
						_vCloseList.front()->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList.front()->getIdX() > _vCloseList[1]->getIdX())
						{
							_vCloseList.front()->routeRender(2, 2);
						}
						else
						{
							_vCloseList.front()->routeRender(3, 2);
						}
					}
				}
			}
			else if (_endTile->getIdY() == _vCloseList.front()->getIdY())
			{
				if (_vCloseList.front()->getIdX() > _endTile->getIdX())
				{
					_endTile->routeRender(0, 3);
					if (_vCloseList.front()->getIdY() == _vCloseList[1]->getIdY())
					{
						_vCloseList.front()->routeRender(0, 1);
					}
					else
					{
						if (_vCloseList.front()->getIdY() > _vCloseList[1]->getIdY())
						{
							_vCloseList.front()->routeRender(0, 2);
						}
						else
						{
							_vCloseList.front()->routeRender(2, 2);
						}
					}
				}
				else
				{
					_endTile->routeRender(1, 3);
					if (_vCloseList.front()->getIdY() == _vCloseList[1]->getIdY())
					{
						_vCloseList.front()->routeRender(1, 1);
					}
					else
					{
						if (_vCloseList.front()->getIdY() > _vCloseList[1]->getIdY())
						{
							_vCloseList.front()->routeRender(1, 2);
						}
						else
						{
							_vCloseList.front()->routeRender(3, 2);
						}
					}
				}
			}
		}
		if (_vCloseList.size() == 2)
		{
			if (_startTile->getIdX() == _vCloseList[1]->getIdX())
			{
				if (_startTile->getIdY() > _vCloseList[1]->getIdY())
				{
					_startTile->routeRender(2, 0);
					if (_vCloseList[0]->getIdX() == _vCloseList[1]->getIdX())
					{
						_vCloseList[1]->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList[0]->getIdX() > _vCloseList[1]->getIdX())
						{
							_vCloseList[1]->routeRender(3, 2);
						}
						else
						{
							_vCloseList[1]->routeRender(2, 2);
						}
					}
				}
				else
				{
					_startTile->routeRender(3, 0);
					if (_vCloseList[0]->getIdX() == _vCloseList[1]->getIdX())
					{
						_vCloseList[1]->routeRender(3, 1);
					}
					else
					{
						if (_vCloseList[0]->getIdX() > _vCloseList[1]->getIdX())
						{
							_vCloseList[1]->routeRender(1, 2);
						}
						else
						{
							_vCloseList[1]->routeRender(0, 2);
						}
					}
				}
			}
			else if (_startTile->getIdY() == _vCloseList[1]->getIdY())
			{
				if (_startTile->getIdX() > _vCloseList[1]->getIdX())
				{
					_startTile->routeRender(0, 0);
					if (_vCloseList[0]->getIdY() == _vCloseList[1]->getIdY())
					{
						_vCloseList[1]->routeRender(0, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdY() > _vCloseList[0]->getIdY())
						{
							_vCloseList[1]->routeRender(1, 2);
						}
						else
						{
							_vCloseList[1]->routeRender(3, 2);
						}
					}
				}
				else
				{
					_startTile->routeRender(1, 0);
					if (_vCloseList[0]->getIdY() == _vCloseList[1]->getIdY())
					{
						_vCloseList[1]->routeRender(1, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdY() > _vCloseList[0]->getIdY())
						{
							_vCloseList[1]->routeRender(0, 2);
						}
						else
						{
							_vCloseList[1]->routeRender(2, 2);
						}
					}
				}
			}



			if (_endTile->getIdX() == _vCloseList[0]->getIdX())
			{
				if (_endTile->getIdY() > _vCloseList[0]->getIdY())
				{
					_endTile->routeRender(3, 3);
					if (_vCloseList[1]->getIdX() == _vCloseList[0]->getIdX())
					{
						_vCloseList[0]->routeRender(2, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdX() > _vCloseList[0]->getIdX())
						{
							_vCloseList[0]->routeRender(3, 2);
						}
						else
						{
							_vCloseList[0]->routeRender(2, 2);
						}
					}
				}
				else
				{
					_endTile->routeRender(2, 3);
					if (_vCloseList[1]->getIdX() == _vCloseList[0]->getIdX())
					{
						_vCloseList[0]->routeRender(3, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdX() > _vCloseList[0]->getIdX())
						{
							_vCloseList[0]->routeRender(1, 2);
						}
						else
						{
							_vCloseList[0]->routeRender(3, 2);
						}
					}
				}
			}
			else if (_endTile->getIdY() == _vCloseList[0]->getIdY())
			{
				if (_endTile->getIdX() > _vCloseList[0]->getIdX())
				{
					_endTile->routeRender(1, 3);
					if (_vCloseList[1]->getIdY() == _vCloseList[0]->getIdY())
					{
						_vCloseList[0]->routeRender(0, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdY() > _vCloseList[0]->getIdY())
						{
							_vCloseList[0]->routeRender(3, 2);
						}
						else
						{
							_vCloseList[0]->routeRender(1, 2);
						}
					}
				}
				else
				{
					_endTile->routeRender(0, 3);
					if (_vCloseList[1]->getIdY() == _vCloseList[0]->getIdY())
					{
						_vCloseList[0]->routeRender(1, 1);
					}
					else
					{
						if (_vCloseList[1]->getIdY() > _vCloseList[0]->getIdY())
						{
							_vCloseList[0]->routeRender(2, 2);
						}
						else
						{
							_vCloseList[0]->routeRender(0, 2);
						}
					}
				}
			}

		}
		if (_vCloseList.size() == 1)
		{
			if (_startTile->getIdX() == _vCloseList[0]->getIdX())
			{
				if (_startTile->getIdY() > _vCloseList[0]->getIdY())
				{
					_startTile->routeRender(2, 0);
					if (_vCloseList[0]->getIdX() == _endTile->getIdX())
					{
						_vCloseList[0]->routeRender(2, 1);
						_endTile->routeRender(2, 3);
					}
					else
					{
						if (_vCloseList[0]->getIdX() > _endTile->getIdX())
						{
							_vCloseList[0]->routeRender(2, 2);
							_endTile->routeRender(3, 3);
						}
						else
						{
							_vCloseList[0]->routeRender(3, 2);
							_endTile->routeRender(1, 3);
						}
					}
				}
				else
				{
					_startTile->routeRender(3, 0);
					if (_vCloseList[0]->getIdX() == _endTile->getIdX())
					{
						_vCloseList[0]->routeRender(3, 1);
						_endTile->routeRender(3, 3);
					}
					else
					{
						if (_vCloseList[0]->getIdX() > _endTile->getIdX())
						{
							_vCloseList[0]->routeRender(0, 2);
							_endTile->routeRender(2, 3);
						}
						else
						{
							_vCloseList[0]->routeRender(1, 2);
							_endTile->routeRender(2, 3);
						}
					}
				}
			}
			else if (_startTile->getIdY() == _vCloseList[0]->getIdY())
			{
				if (_startTile->getIdX() > _vCloseList[0]->getIdX())
				{
					_startTile->routeRender(0, 0);
					if (_vCloseList[0]->getIdY() == _endTile->getIdY())
					{
						_vCloseList[0]->routeRender(0, 1);
						_endTile->routeRender(0, 3);
					}
					else
					{
						if (_vCloseList[0]->getIdY() > _endTile->getIdY())
						{
							_vCloseList[0]->routeRender(1, 2);
							_endTile->routeRender(2, 3);
						}
						else
						{
							_vCloseList[0]->routeRender(3, 2);
							_endTile->routeRender(3, 3);
						}
					}
				}
				else
				{
					_startTile->routeRender(1, 0);
					if (_vCloseList[0]->getIdY() == _endTile->getIdY())
					{
						_vCloseList[0]->routeRender(1, 1);
						_endTile->routeRender(1, 3);
					}
					else
					{
						if (_vCloseList[0]->getIdY() > _endTile->getIdY())
						{
							_vCloseList[0]->routeRender(0, 2);
							_endTile->routeRender(2, 3);
						}
						else
						{
							_vCloseList[0]->routeRender(2, 2);
							_endTile->routeRender(3, 3);
						}
					}
				}
			}
		}
	}
	else
	{
		if (_startTile->getIdX() == _endTile->getIdX())
		{
			if (_startTile->getIdY() > _endTile->getIdY())
			{

				_startTile->routeRender(2, 0);
				_endTile->routeRender(2, 3);
			}
			else
			{

				_startTile->routeRender(3, 0);
				_endTile->routeRender(3, 3);
			}
		}
		else if (_startTile->getIdY() == _endTile->getIdY())
		{
			if (_startTile->getIdX() > _endTile->getIdX())
			{

				_startTile->routeRender(0, 0);
				_endTile->routeRender(0, 3);
			}
			else
			{

				_startTile->routeRender(1, 0);
				_endTile->routeRender(1, 3);
			}
		}
	}
}


