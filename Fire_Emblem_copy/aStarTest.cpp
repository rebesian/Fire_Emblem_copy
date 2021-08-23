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
	_count = 0;
	_start = false;
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

void aStarTest::update()
{

	if (KEYMANAGER->isToggleKey(VK_TAB))
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

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int y = 0; y < _vTotalList.size(); ++y)					
		{
			for (int x = 0; x < _vTotalList[y].size(); ++x)
			{
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
		//for (int i = 0; i < _vCloseList.size(); ++i)
		//{
		//
		//	RECT temp = _vCloseList[i]->getRect();
		//	Rectangle(_map->getMapDC(), temp);
		//}
	}
}

//Ÿ�� ���� �Լ�
void aStarTest::setTile(int playerX, int playerY)
{
	_vTotalList.clear();

	_startTile = new tile;
	_startTile->setLinkMap(_map);
	_startTile->init(playerX, playerY);
	_startTile->setAttribute("move");

	_currentTile = _startTile;
	
	int idx = 0;
	int idy = 0;
	for (int y = playerY - _totalRange; y <= _totalRange + playerY; ++y)
	{
		vector<tile*> TotalList;
		idx = 0;
		for (int x = playerX - _totalRange ; x <= _totalRange + playerX; ++x)
		{
					
			if (y < 0 || x<0 || x>_map->getSizeX() || y>_map->getSizeY())
			{
				continue;
			}
			if (x == playerX && playerY == y)
			{
				TotalList.push_back(_startTile);
				playerIdx = idx;
				playerIdy = idy;
				continue;
			}
			++idx;
			tile* node = new tile;
			node->setLinkMap(_map);
			node->init(x, y);
			TotalList.push_back(node);
		}
		++idy;
		_vTotalList.push_back(TotalList);
	}

	_movecount = _moveRange;

	//�� Move�ֱ�
	for (int i = 1; i < playerIdy; ++i)
	{
		if (playerIdy - i < 0) break;
		if (_map->getTerrain(playerX, playerY-i) == TR_MOUNTIN) _movecount = 0;
		if (_movecount != 0)
		{
			_vTotalList[playerIdy - i][playerIdx]->setAttribute("move");
			--_movecount;
		}
		else
			break;

	}

	_movecount = _moveRange;
	

	//�� Move�ֱ�
	for (int i = 1; i <=_vTotalList.size()-playerIdy; ++i)
	{
		if (playerY + i > _map->getSizeY()) break;
		if (_map->getTerrain(playerX, playerY + i) == TR_MOUNTIN) _movecount = 0;
		if (_movecount != 0)
		{
			_vTotalList[playerIdy + i][playerIdx]->setAttribute("move");
			_movecount--;
		}
		else
			break;
	}
	
	_movecount = _moveRange;

	
	//�� move�ֱ�
	for (int i = 1; i <= playerIdx; ++i)
	{
		if (playerX - i < 0) break;
		if (_map->getTerrain(playerX-i,playerY) == TR_MOUNTIN) _movecount=0;
		if (_movecount > 0)
		{
			_vTotalList[playerIdy][playerIdx - i]->setAttribute("move");
			--_movecount;
		}
		else
			break;

	}
	
	_movecount = _moveRange;
	
	//�� move�ֱ�			
	for (int i = 1; i <= _vTotalList[playerIdy].size()-playerIdx; ++i)
	{
		if (playerX + i > _map->getSizeX()) break;
		if (_map->getTerrain(playerX + i, playerY) == TR_MOUNTIN) _movecount = 0;
		if (_movecount > 0)
		{
			_vTotalList[playerIdy][playerIdx + i]->setAttribute("move");
			--_movecount;
		}
		else
			break;
	}

	//1��и� move�ֱ�
	for(int y = 1; y < playerIdy; ++y)
	{
		_movecount = _moveRange;

		if (playerY - y < 0)
			break;
		_movecount -= y;
		for (int x = 1; x <= (_vTotalList[playerIdy].size() - playerIdx) - y ; ++x)
		{
			if (playerX + x > _map->getSizeX())
				break;
			if (_map->getTerrain(playerX + x, playerY - y) == TR_MOUNTIN) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerIdy - y][playerIdx + x]->setAttribute("move");
				--_movecount;
			}
			else
				break;

		}
	}
	//2��и� move�ֱ�
	for (int y = 1; y < playerIdy; ++y)
	{
		_movecount = _moveRange;

		if (playerY - y < 0)
			break;
		_movecount -= y;
		for (int x = 1; x <= playerIdx - y; ++x)
		{
			if (playerX - x < 0)
				break;
			if (_map->getTerrain(playerX - x, playerY - y) == TR_MOUNTIN) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerIdy - y][playerIdx - x]->setAttribute("move");
				--_movecount;
			}
			else
				break;
		
		}
	}
	
	//3��и� move�ֱ�
	for (int y = 1; y <= _vTotalList.size() - playerIdy; ++y)
	{
		_movecount = _moveRange;
		
		if (playerY + y > _map->getSizeY())
			break;
		_movecount -= y;
		for (int x = 1; x <= playerIdx - y; ++x)
		{
			if (playerX - x < 0)
				break;
			if (_map->getTerrain(playerX - x, playerY + y) == TR_MOUNTIN) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerIdy + y][playerIdx - x]->setAttribute("move");
				--_movecount;
			}
			else
				break;
		}
	}
	//4��и� move�ֱ�
	for (int y = 1; y <= _vTotalList.size() - playerIdy; ++y)
	{
		_movecount = _moveRange;
		
		if (playerY + y > _map->getSizeY())
			break;
		_movecount -= y;
		for (int x = 1; x < (_vTotalList[playerIdy].size() - playerIdx) - y; ++x)
		{
			if (playerX + x > _map->getSizeX())
				break;
			if (_map->getTerrain(playerX + x, playerY + y) == TR_MOUNTIN) _movecount = 0;
			if (_movecount > 0)
			{
				_vTotalList[playerIdy + y][playerIdx + x]->setAttribute("move");
				--_movecount;
			}
			else
				break;
		}
	}


	//attack�ֱ�
	for (int y = 0; y < _vTotalList.size(); ++y)
	{
		for (int x = 0; x < _vTotalList[y].size(); ++x)
		{
			if (_vTotalList[y][x]->getAttribute() == "move")
			{
				int range = 0;
				//����
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j < _attackRange; ++j)
					{
						if (_vTotalList[y + i][x + range + j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x + range + j]->setAttribute("attack");
						}
						
					}
					if (i < 0)
						range++;
					else
						range--;
				}

				range = 0;
				//������
				for (int i = -_attackRange; i <= _attackRange; ++i)
				{
					for (int j = 0; j < _attackRange; ++j)
					{
						if (x - range - j < 0) continue;
						if (_vTotalList[y + i][x - range - j]->getAttribute() == "none")
						{
							_vTotalList[y + i][x - range - j]->setAttribute("attack");
						}

					}
					if (i < 0)
						range++;
					else
						range--;
				}
			}
		}
	}

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
		while (_currentTile->getParentNode() != NULL)
		{
			_vCloseList.emplace_back(_currentTile);
			_vOpenList.clear();
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

void aStarTest::enemyEndSelect(int enemyIndexX, int enemyIndexY , int playerIndexX, int playerIndexY)
{
	int SelectX = abs(enemyIndexX - playerIndexX);
	int SelectY = abs(enemyIndexY - playerIndexY);
	if (SelectX > _totalRange)
	{
		SelectX = _totalRange;
	
	}
	if (SelectY > _totalRange)
	{
		SelectY = _totalRange;
	}
	if (enemyIndexX > playerIndexX)
		SelectX *= -1;
	if (enemyIndexY > playerIndexY)
		SelectY *= -1;


	_endTile = new tile;
	_endTile->setLinkMap(_map);
	_endTile->init(playerIndexX, playerIndexY);
	_endTile->setAttribute("heal");
	_endTile->setIsEnd(true);
	_vTotalList[playerIdy + SelectY].erase(_vTotalList[playerIdy + SelectY].begin() + (playerIdx + SelectX));
	_vTotalList[playerIdy + SelectY].insert(_vTotalList[playerIdy + SelectY].begin() + (playerIdx + SelectX), _endTile);
	//RECT rc;
	
	//if (_endTile->getIdX() != playerIndexX || _endTile->getIdY() != playerIndexY)
	//{
	//	ismove = true;
	//}
	//if (ismove) {
	//	for (int i = 0; i < _vTotalList.size(); ++i)
	//	{
	//		if (_vTotalList[i]->getAttribute() == "player")
	//		{
	//			if (_vTotalList[(playerIndexY*_TotaltileX + playerIndexX)]->getAttribute() == "enemy") break;
	//			node = new tile;
	//			node->setLinkRandomMap(_map);
	//			node->init(_endTile->getIdX(), _endTile->getIdY());
	//			_endTile->setIdX(playerIndexX);
	//			_endTile->setIdY(playerIndexY);
	//
	//			rc = _map->getRect(_endTile->getIdX(), _endTile->getIdY());
	//			_endTile->setRect(rc);
	//			_endTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	//			_vTotalList.erase(_vTotalList.begin() + i);
	//			_vTotalList.insert(_vTotalList.begin() + i, node);
	//			_vTotalList.erase(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX));
	//			_vTotalList.insert(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX), _endTile);
	//			break;
	//		}
	//	}
	//	for (int i = 0; i < _vTotalList.size(); ++i)
	//	{
	//		if (!(_vTotalList[i]->getAttribute() == "player" || _vTotalList[i]->getAttribute() == "enemy"))
	//		{
	//			_vTotalList[i]->setParentNode(nullptr);
	//			_vTotalList[i]->setCostFromStart(0);
	//			_vTotalList[i]->setCostToGoal(0);
	//			_vTotalList[i]->setTotalCost(0);
	//			_vTotalList[i]->setColor(RGB(255, 255, 255));
	//			_vTotalList[i]->setIsOpen(true);
	//		}
	//	}
	//	_vCloseList.clear();
	//	_vOpenList.clear();
	//	_endTile->setIsOpen(true);
	//	_currentTile = _startTile;
	//}
}

//void aStarTest::start()
//{
//
//	if (_vCloseList.size() != 0) {
//		{
//			move(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY());
//			if (_vCloseList.size() >= 1)
//			{
//				_damagecount = 0;
//				_vCloseList.erase(_vCloseList.end() - 1);
//			}
//			//�÷��̾ ��γ��Ѵµ� �������� ������������
//			if (_vCloseList.size() == 0)
//			{
//				if (_startTile->getIdX() == _endTile->getIdX())
//				{
//					if (_endTile->getIdY() == _startTile->getIdY() + 1)
//					{
//						//hp�ް��Ҳ���
//						_damagecount++;
//						if (_damagecount > 1)
//						{
//							damage = true;
//							_dir = DOWN;
//						}
//					}
//					else if (_endTile->getIdY() == _startTile->getIdY() - 1)
//					{
//						//hp�ް��Ҳ���
//						_damagecount++;
//						if (_damagecount > 1)
//						{
//							damage = true;
//							_dir = UP;
//						}
//					}
//				}
//				else if (_startTile->getIdY() == _endTile->getIdY())
//				{
//					if (_endTile->getIdX() == _startTile->getIdX() + 1)
//					{
//						//hp�ް��Ҳ���
//						_damagecount++;
//						if (_damagecount > 1)
//						{
//							damage = true;
//							_dir = RIGHT;
//						}
//					}
//					else if (_endTile->getIdX() == _startTile->getIdX() - 1)
//					{
//						//hp�ް��Ҳ���
//						_damagecount++;
//						if (_damagecount > 1)
//						{
//							damage = true;
//							_dir = LEFT;
//						}
//					}
//				}
//			}
//		}
//	}
//	else if (_vCloseList.size() == 0)
//	{
//		if ((_startTile->getIdX() == _endTile->getIdX() && (_endTile->getIdY() && _startTile->getIdY() + 1 || _endTile->getIdY() && _startTile->getIdY() - 1)) ||
//			(_startTile->getIdY() == _endTile->getIdY() && (_endTile->getIdX() && _startTile->getIdX() + 1 || _endTile->getIdX() && _startTile->getIdX() - 1)))
//		{
//			//hp�ް��Ҳ���
//			damage = true;
//			if (_startTile->getIdX() == _endTile->getIdX())
//			{
//				if (_endTile->getIdY() == _startTile->getIdY() + 1)
//				{
//
//					_dir = DOWN;
//				}
//				else if (_endTile->getIdY() == _startTile->getIdY() - 1)
//				{
//
//					_dir = UP;
//				}
//			}
//			else if (_startTile->getIdY() == _endTile->getIdY())
//			{
//				if (_endTile->getIdX() == _startTile->getIdX() + 1)
//				{
//					_dir = RIGHT;
//
//				}
//				else if (_endTile->getIdX() == _startTile->getIdX() - 1)
//				{
//					_dir = LEFT;
//
//				}
//			}
//		}
//	}
//
//}

void aStarTest::move(int X, int Y)
{
	//RECT rc;
	//tile* node = new tile;
	//node->setLinkRandomMap(_map);
	//node->init(_startTile->getIdX(), _startTile->getIdY());
	//_startTile->setIdX(X);
	//_startTile->setIdY(Y);
	//rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	//_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	//_startTile->setRect(rc);
	//_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	//_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	//_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	//_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
	//if (_vCloseList.size() >= 1)
	//{
	//	_damagecount = 0;
	//	_vCloseList.erase(_vCloseList.end() - 1);
	//}
	//if (_vCloseList.size() == 0)
	//{
	//	if (_startTile->getIdX() == _endTile->getIdX())
	//	{
	//		if (_endTile->getIdY() == _startTile->getIdY() + 1)
	//		{
	//			//hp�ް��Ҳ���
	//			_damagecount++;
	//			if (_damagecount > 1)
	//			{
	//				damage = true;
	//				_dir = DOWN;
	//			}
	//		}
	//		else if (_endTile->getIdY() == _startTile->getIdY() - 1)
	//		{
	//			//hp�ް��Ҳ���
	//			_damagecount++;
	//			if (_damagecount > 1)
	//			{
	//				damage = true;
	//				_dir = UP;
	//			}
	//		}
	//	}
	//	else if (_startTile->getIdY() == _endTile->getIdY())
	//	{
	//		if (_endTile->getIdX() == _startTile->getIdX() + 1)
	//		{
	//			//hp�ް��Ҳ���
	//			_damagecount++;
	//			if (_damagecount > 1)
	//			{
	//				damage = true;
	//				_dir = RIGHT;
	//			}
	//		}
	//		else if (_endTile->getIdX() == _startTile->getIdX() - 1)
	//		{
	//			//hp�ް��Ҳ���
	//			_damagecount++;
	//			if (_damagecount > 1)
	//			{
	//				damage = true;
	//				_dir = LEFT;
	//			}
	//		}
	//	}
	//}
}

void aStarTest::actionMove(int X, int Y)
{
	//RECT rc;
	//tile* node = new tile;
	//node->setLinkRandomMap(_map);
	//node->init(_startTile->getIdX(), _startTile->getIdY());
	//_startTile->setIdX(X);
	//_startTile->setIdY(Y);
	//rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	//_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	//_startTile->setRect(rc);
	//_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	//_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	//_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	//_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
}

void aStarTest::callPathFinder()
{
	_vCloseList.clear();
	_vOpenList.clear();
	pathFinder(_startTile);
}

void aStarTest::enemyAttack()
{
	if (_startTile->getIdX() == _endTile->getIdX())
	{
		if (_endTile->getIdY() == _startTile->getIdY() + 1)
		{
			//hp�ް��Ҳ���
			damage = true;
			_dir = DOWN;

		}
		else if (_endTile->getIdY() == _startTile->getIdY() - 1)
		{
			//hp�ް��Ҳ���
			damage = true;
			_dir = UP;

		}
	}
	else if (_startTile->getIdY() == _endTile->getIdY())
	{
		if (_endTile->getIdX() == _startTile->getIdX() + 1)
		{
			//hp�ް��Ҳ���
			damage = true;
			_dir = RIGHT;

		}
		else if (_endTile->getIdX() == _startTile->getIdX() - 1)
		{
			//hp�ް��Ҳ���
			damage = true;
			_dir = LEFT;

		}
	}
}
