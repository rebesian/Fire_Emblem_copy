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
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;
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
	int _damagecount;
	float time;
	bool _start; // �׳� ���ۿ�
	bool ismove;
	bool damage;
	bool isMiniboss;
	int _TotaltileX,_TotaltileY;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int playerX, int playerY,int moveRange);
	void release();
	void update();
	void render();
	//Ÿ�� ���� �Լ�
	void setTile(int playerX, int playerY);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);
	void endmove(int playerIndexX, int playerIndexY);
	void start();
	void move(int X ,int Y);
	void actionMove(int X, int Y);
	void callPathFinder(int x, int y);
	void enemyAttack();

	void setLinkrandomMap(tileSet* map) { _map = map; }

	//����
	int getEnemyTileX() { return _startTile->getIdX(); }
	int getEnemyTileY() { return _startTile->getIdY(); }
	bool getDamage() { return damage; }
	bool getStart() { return _start; }
	PLAYER_ENEMY_DIRECTION getDirection() { return _dir; };
	int getCloseListsize() { return _vCloseList.size(); }
	int getClosebackX() { return _vCloseList.back()->getIdX(); }
	int getClosebackY() { return _vCloseList.back()->getIdY(); }


	//����
	void setDamage(bool _damage) { damage = _damage; }
	void clear() { _vCloseList.clear(); _vOpenList.clear(); }
};
