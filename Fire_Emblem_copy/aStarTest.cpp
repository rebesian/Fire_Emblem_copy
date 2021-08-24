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
	sprintf_s(str, "Ÿ�ٿ���><");

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
				//sprintf_s(str, "x:%d,y:%d", x,y);
				//TextOut(_map->getMapDC(), _vTotalList[y][x]->getRect().left, _vTotalList[y][x]->getRect().top, str, strlen(str));
			}
		}

	}
}

//Ÿ�� ���� �Լ�
void aStarTest::setTile(int playerX, int playerY)
{
	_vTotalList.clear();
	_moveTileCount = 0;
	_startTile = new tile;
	_startTile->setLinkMap(_map);
	_startTile->init(playerX, playerY);
	_startTile->setAttribute("move");

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

//�����ִ±��߰��Լ�
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
			//����ó��
			if (!node->getIsOpen()) continue;

			//���� Ÿ�� ��� �������ش�.
			node->setParentNode(_currentTile);
			//node->setparentNumber(_currentTile->getparentNumber() + 1);
			//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			////���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
			//if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

			//�̹� üũ�Ⱦִ� �ǳʶڴ�
			if (!addObj) continue;
			//�����ִ� ���� ���Ϳ� ����ȴ�
			_vOpenList.push_back(node);

		}
		if (i == 1 || i == 3)
		{
			if (startY - 2 + i < 0 || startY - 2 + i >= _map->getSizeY()) continue;
			tile* node = _vTotalList[startY-2+i][startX];
			//����ó��
			if (!node->getIsOpen()) continue;

			//���� Ÿ�� ��� �������ش�.
			node->setParentNode(_currentTile);
			//node->setparentNumber(_currentTile->getparentNumber() + 1);

			//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}


			//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
			//if (node->getAttribute() != "player");

			//�̹� üũ�Ⱦִ� �ǳʶڴ�
			if (!addObj) continue;
			//�����ִ� ���� ���Ϳ� ����ȴ�
			_vOpenList.push_back(node);

		}

	}
	
	return _vOpenList;
}

//�� ã�� �Լ�
void aStarTest::pathFinder(tile * currentTile)
{
	//�񱳿� ������κ�뼳��
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	//���¸���Ʈ ���;ȿ���, ���������θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H������ (������������ ����������)
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) + abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//���� start���� Ÿ������
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//���¸���Ʈ�� �ش� Ÿ������
		POINT center2 = _vOpenList[i]->getCenter();

		//G������ (ó���������� ������������)
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y));

		//F = G + H �Ѱ����ϱ�sv
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getFromCost() + _vOpenList[i]->getToGoal());
		//�׷��� �̾Ƴ� �� ��� ������ ������ ��κ��� �����Ͽ� ���� �������� ��� �̾Ƴ���.
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			//�� ����Ÿ�ϰ��� �ִ´�
			tempTile = _vOpenList[i];
		}

		//�������ΰ� üũ��
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			//�̹� �������̶�� ������ٸ�?
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		//��Ȯ�ξ��Ϸ��� Openfalse
		_vOpenList[i]->setIsOpen(false);
		//�ߺ�üũ���ƴ϶��
		if (!addObj) continue;
		//�ߺ��̾ȉ�ٸ� ���� �־��ش�
		_vOpenList.push_back(tempTile);
	}


	if (tempTile == nullptr)
	{
		return;
	}
	else if (tempTile->getIsEnd())
	{
		//�ִܰ�θ� ��ĥ�����
		while (_currentTile != _startTile)
		{
			_vCloseList.emplace_back(_currentTile);
			_vOpenList.clear();
			_start = true;
			_currentTile = _currentTile->getParentNode();
		}
		return;
	}

	//�ִܰ�θ� �־�J����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�� ���¸���Ʈ���� �������ݽô�
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
	
	_endTile = new tile;
	_endTile->setLinkMap(_map);
	_endTile->init(endIndexX, endIndexY);
	_endTile->setAttribute("heal");
	_endTile->setIsEnd(true);
	_vTotalList[endIndexY].erase(_vTotalList[endIndexY].begin() + (endIndexX));
	_vTotalList[endIndexY].insert(_vTotalList[endIndexY].begin() + (endIndexX), _endTile);
	
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

	//�� Move�ֱ�
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


	//�� Move�ֱ�
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


	//�� move�ֱ�
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

	//�� move�ֱ�			
	for (int i = 1; i <= _moveRange; ++i)
	{
		if (playerX + i > _map->getSizeX()) break;
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

	//1��и� move�ֱ�
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY - y < 0)
			break;
		_movecount -= y;
		for (int x = 1; x <= _moveRange - y; ++x)
		{
			if (playerX + x > _map->getSizeX())
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
	//2��и� move�ֱ�
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

	//3��и� move�ֱ�
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY + y > _map->getSizeY())
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

	//4��и� move�ֱ�
	for (int y = 1; y <= _moveRange; ++y)
	{
		_movecount = _moveRange;

		if (playerY + y > _map->getSizeY())
			break;
		_movecount -= y;
		for (int x = 1; x <=_moveRange - y; ++x)
		{
			if (playerX + x > _map->getSizeX())
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


	//attack�ֱ�
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
				//����
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j <= abs(i+z); ++j)
					{
						if (y + i <0 || y + i > _map->getSizeY() || x + j >_map->getSizeX()) continue;
						if (_vTotalList[y + i][x + j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x + j]->setAttribute("attack");
						}

					}
					if (i >= 0)
						z = -_attackRange;
				}

				z = _attackRange;
				//������
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j <= abs(i + z); ++j)
					{
						if ( y+i <0|| y + i > _map->getSizeY() || x - j < 0) continue;
						if (_vTotalList[y + i][x - j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x - j]->setAttribute("attack");
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
	_vCloseList.clear();
	_vOpenList.clear();
	pathFinder(_startTile);
}


