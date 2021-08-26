#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class mapGenerator;

class aStarTest : public gameNode
{
private:
	//��ü Ÿ�� ���� ����
	vector<vector<tile*>> _vTotalList;
	vector<vector<tile*>> ::iterator _viTotalList;
	//�� �� �ִ� Ÿ�� ���� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;
	//���� ����� ��θ� ���� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile; //����Ÿ�� 
	tile* _endTile; //��Ÿ��
	tile* _currentTile; //���� Ÿ��

	tileSet* _map;
	PLAYER_ENEMY_DIRECTION _dir;

	int _count;// �׳ɷ�����
	int _movecount,_attackCount , _moveTileCount;
	int _totalRange , _moveRange, _attackRange;
	int playerIdx, playerIdy;
	int routeX, routeY;

	float time;
	bool _start; // �׳� ���ۿ�
	bool ismove, _render;
	bool damage;
	bool isMiniboss;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int playerX, int playerY,int moveRange, int attackRange);
	void release();
	void update(bool render);
	void render();
	//Ÿ�� ���� �Լ�
	void setTile(int playerX, int playerY);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);



	void EndSelect(int endIndexX, int endIndexY);
	void setMoveTile(int playerX, int playerY);


	void move(int X ,int Y);
	void callPathFinder();
	
	void route();

	void setLinkMap(tileSet* map) { _map = map; }


	//����
	int getEnemyTileX() { return _startTile->getIdX(); }
	int getEnemyTileY() { return _startTile->getIdY(); }
	int getTargetTileX() { return _endTile->getIdX(); }
	int getTargetTileY() { return _endTile->getIdY(); }
	bool getDamage() { return damage; }
	bool getStart() { return _start; }
	PLAYER_ENEMY_DIRECTION getDirection() { return _dir; };
	string getAttribute(int x, int y) { return _vTotalList[y][x]->getAttribute(); }
	int getCloseListsize() { return _vCloseList.size(); }
	int getClosebackX() { return _vCloseList.back()->getIdX(); }
	int getClosebackY() { return _vCloseList.back()->getIdY(); }


	//����
	void setDamage(bool _damage) { damage = _damage; }
	void setStart(bool start) { _start = start; }
	void clear() { _vCloseList.clear(); _vOpenList.clear(); }
};

