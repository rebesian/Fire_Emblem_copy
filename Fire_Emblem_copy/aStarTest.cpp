#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init(int playerX, int playerY, int moveRange)
{
	_count = _damagecount = 0;
	_start = false;
	damage = false;
	_TotaltileX = moveRange;
	_TotaltileY = moveRange;
	setTile(playerX, playerY);
	time = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void aStarTest::release()
{

}

void aStarTest::update()
{

	//pathFinder(_currentTile);

}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}
}

//Ÿ�� ���� �Լ�
void aStarTest::setTile(int playerX, int playerY)
{
	_startTile = new tile;
	_startTile->setLinkRandomMap(_map);
	_startTile->init(playerX, playerY);

	_currentTile = _startTile;

	for (int i = playerY; i < _TotaltileY; ++i)
	{
		for (int j = playerX; j < _TotaltileX; ++j)
		{

			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 0));
				_vTotalList.push_back(_startTile);
				continue;
			}
			tile* node = new tile;
			node->setLinkRandomMap(_map);
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}

}
//�����ִ±��߰��Լ�
vector<tile*> aStarTest::addOpenList(tile * currentTile)
{

	int startX = currentTile->getIdX();
	int startY = currentTile->getIdY() - 1;

	if (startY < _endTile->getIdY())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 0 || i == 2)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX + (i*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 1)
			{

				tile* node = _vTotalList[(startY*_TotaltileX) + startX + i + (i*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX - 1 + ((i - 2)*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);
			}

		}
	}
	else
	{
		for (int i = 3; i >= 0; --i)
		{
			if (i == 0 || i == 2)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX + (i*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 1)
			{

				tile* node = _vTotalList[(startY*_TotaltileX) + startX + i + (i*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX - 1 + ((i - 2)*_TotaltileX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
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
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);
			}

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

		//F = G + H �Ѱ����ϱ�
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
	else if (tempTile->getAttribute() == "player")
	{
		//�ִܰ�θ� ��ĥ�����
		while (_currentTile->getParentNode() != NULL)
		{
			_vCloseList.emplace_back(_currentTile);
			//_vOpenList.clear();
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
			_start = true;
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
	//pathFinder(_currentTile);

}

void aStarTest::endmove(int playerIndexX, int playerIndexY)
{
	RECT rc;
	tile* node;
	if (_endTile->getIdX() != playerIndexX || _endTile->getIdY() != playerIndexY)
	{
		ismove = true;
	}
	if (ismove) {
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "player")
			{
				if (_vTotalList[(playerIndexY*_TotaltileX + playerIndexX)]->getAttribute() == "enemy") break;
				node = new tile;
				node->setLinkRandomMap(_map);
				node->init(_endTile->getIdX(), _endTile->getIdY());
				_endTile->setIdX(playerIndexX);
				_endTile->setIdY(playerIndexY);

				rc = _map->getRect(_endTile->getIdX(), _endTile->getIdY());
				_endTile->setRect(rc);
				_endTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
				_vTotalList.erase(_vTotalList.begin() + i);
				_vTotalList.insert(_vTotalList.begin() + i, node);
				_vTotalList.erase(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX));
				_vTotalList.insert(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX), _endTile);
				break;
			}
		}
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (!(_vTotalList[i]->getAttribute() == "player" || _vTotalList[i]->getAttribute() == "enemy"))
			{
				_vTotalList[i]->setParentNode(nullptr);
				_vTotalList[i]->setCostFromStart(0);
				_vTotalList[i]->setCostToGoal(0);
				_vTotalList[i]->setTotalCost(0);
				_vTotalList[i]->setColor(RGB(255, 255, 255));
				_vTotalList[i]->setIsOpen(true);
			}
		}
		_vCloseList.clear();
		_vOpenList.clear();
		_endTile->setIsOpen(true);
		_currentTile = _startTile;
	}
}

void aStarTest::start()
{

	if (_vCloseList.size() != 0) {
		{
			move(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY());
			if (_vCloseList.size() >= 1)
			{
				_damagecount = 0;
				_vCloseList.erase(_vCloseList.end() - 1);
			}
			//�÷��̾ ��γ��Ѵµ� �������� ������������
			if (_vCloseList.size() == 0)
			{
				if (_startTile->getIdX() == _endTile->getIdX())
				{
					if (_endTile->getIdY() == _startTile->getIdY() + 1)
					{
						//hp�ް��Ҳ���
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = DOWN;
						}
					}
					else if (_endTile->getIdY() == _startTile->getIdY() - 1)
					{
						//hp�ް��Ҳ���
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = UP;
						}
					}
				}
				else if (_startTile->getIdY() == _endTile->getIdY())
				{
					if (_endTile->getIdX() == _startTile->getIdX() + 1)
					{
						//hp�ް��Ҳ���
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = RIGHT;
						}
					}
					else if (_endTile->getIdX() == _startTile->getIdX() - 1)
					{
						//hp�ް��Ҳ���
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = LEFT;
						}
					}
				}
			}
		}
	}
	else if (_vCloseList.size() == 0)
	{
		if ((_startTile->getIdX() == _endTile->getIdX() && (_endTile->getIdY() && _startTile->getIdY() + 1 || _endTile->getIdY() && _startTile->getIdY() - 1)) ||
			(_startTile->getIdY() == _endTile->getIdY() && (_endTile->getIdX() && _startTile->getIdX() + 1 || _endTile->getIdX() && _startTile->getIdX() - 1)))
		{
			//hp�ް��Ҳ���
			damage = true;
			if (_startTile->getIdX() == _endTile->getIdX())
			{
				if (_endTile->getIdY() == _startTile->getIdY() + 1)
				{

					_dir = DOWN;
				}
				else if (_endTile->getIdY() == _startTile->getIdY() - 1)
				{

					_dir = UP;
				}
			}
			else if (_startTile->getIdY() == _endTile->getIdY())
			{
				if (_endTile->getIdX() == _startTile->getIdX() + 1)
				{
					_dir = RIGHT;

				}
				else if (_endTile->getIdX() == _startTile->getIdX() - 1)
				{
					_dir = LEFT;

				}
			}
		}
	}

}

void aStarTest::move(int X, int Y)
{
	RECT rc;
	tile* node = new tile;
	node->setLinkRandomMap(_map);
	node->init(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setIdX(X);
	_startTile->setIdY(Y);
	rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	_startTile->setRect(rc);
	_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
	if (_vCloseList.size() >= 1)
	{
		_damagecount = 0;
		_vCloseList.erase(_vCloseList.end() - 1);
	}
	if (_vCloseList.size() == 0)
	{
		if (_startTile->getIdX() == _endTile->getIdX())
		{
			if (_endTile->getIdY() == _startTile->getIdY() + 1)
			{
				//hp�ް��Ҳ���
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = DOWN;
				}
			}
			else if (_endTile->getIdY() == _startTile->getIdY() - 1)
			{
				//hp�ް��Ҳ���
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = UP;
				}
			}
		}
		else if (_startTile->getIdY() == _endTile->getIdY())
		{
			if (_endTile->getIdX() == _startTile->getIdX() + 1)
			{
				//hp�ް��Ҳ���
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = RIGHT;
				}
			}
			else if (_endTile->getIdX() == _startTile->getIdX() - 1)
			{
				//hp�ް��Ҳ���
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = LEFT;
				}
			}
		}
	}
}

void aStarTest::actionMove(int X, int Y)
{
	RECT rc;
	tile* node = new tile;
	node->setLinkRandomMap(_map);
	node->init(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setIdX(X);
	_startTile->setIdY(Y);
	rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	_startTile->setRect(rc);
	_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
}

void aStarTest::callPathFinder(int x,int y)
{
	_vCloseList.clear();
	_vOpenList.clear();
	actionMove(x, y);
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
