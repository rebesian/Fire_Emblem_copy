#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class mapGenerator;

class aStarTest : public gameNode
{
private:
	//전체 타일 담을 벡터
	vector<vector<tile*>> _vTotalList;
	vector<vector<tile*>> ::iterator _viTotalList;
	//갈 수 있는 타일 담을 벡터
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;
	//가장 가까운 경로를 담을 벡터
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;
	//적의 좌표정보를 어떻게 가져와야하나
	vector<tile*> _vEnemy;

	tile* _startTile; //시작타일 
	tile* _endTile; //끝타일
	tile* _currentTile; //현재 타일

	tileSet* _map;
	PLAYER_ENEMY_DIRECTION _dir;

	int _count;// 그냥렌더용
	int _movecount,_attackCount , _moveTileCount;
	int _totalRange , _moveRange, _attackRange;
	int routeX, routeY;

	float time;
	bool _start , _stop;
	bool ismove, _render;
	bool damage;
	bool isMiniboss;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int playerX, int playerY,int moveRange, int attackRange);
	void release();
	void update(bool render);
	void render(TYPE type);
	//타일 셋팅 함수
	void setTile(int playerX, int playerY);
	//갈 수 있는 길을 찾아 담아줄 함수
	vector<tile*> addOpenList(tile* currentTile);
	//길 찾는 함수
	void pathFinder(tile* currentTile);



	void EndSelect(int endIndexX, int endIndexY, bool cancel = false);
	void setMoveTile(int playerX, int playerY , TYPE type);
	void setAttackTile(int playerX, int playerY , TYPE type);

	void move(int X ,int Y);
	void callPathFinder();
	
	void route();

	void setLinkMap(tileSet* map) { _map = map; }


	//겟터
	int getEnemyTileX() { return _startTile->getIdX(); }
	int getEnemyTileY() { return _startTile->getIdY(); }
	int getTargetTileX() { return _endTile->getIdX(); }
	int getTargetTileY() { return _endTile->getIdY(); }
	bool getDamage() { return damage; }
	bool getStart() { return _start; }
	bool getStop() { return _stop; }
	PLAYER_ENEMY_DIRECTION getDirection() { return _dir; };
	string getAttribute(int x, int y) { return _vTotalList[y][x]->getAttribute(); }
	int getCloseListsize() { return _vCloseList.size(); }
	int getClosebackX() { return _vCloseList.back()->getIdX(); }
	int getClosebackY() { return _vCloseList.back()->getIdY(); }
	
	int getEnemysize() { return _vEnemy.size(); }
	int getEnemyX(int i) { return _vEnemy[i]->getIdX(); }
	int getEnemyY(int i) { return _vEnemy[i]->getIdY(); }

	//셋터
	void setDamage(bool _damage) { damage = _damage; }
	void setStart(bool start) { _start = start; }
	void setStop(bool stop) { _stop = stop; }
	void clear() { _vCloseList.clear(); _vOpenList.clear(); }
};

