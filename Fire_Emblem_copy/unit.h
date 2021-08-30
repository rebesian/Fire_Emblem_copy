#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "aStarTest.h"
class unit : public gameNode
{
protected:
	string name;
	tileSet* _map;
	aStarTest* _astar;
	RECT _rc;
	image* _img;
	TYPE _type;
	PLAYER_ENEMY_DIRECTION _dir;



	int indexX, indexY;
	int moveRange;

	int _hp;
	int attack;
	int critcal;
	int speed;
	float stageX, stageY;
	float battleX, battleY;
	float exp;
	int avoid;

	bool use, battle;

	int stageRenderX;
	int stageRenderY;
	bool _render , _moving, _pointing, _playerSelect, _moveSelect ,_attackSelect;
	int battleRender;

	int stageRenderCount;
	int battleRenderCount;
public:
	virtual HRESULT init(int idx, int idy, int moveRange,TYPE type);
	virtual void update(int idx, int idy);
	virtual void release();
	virtual void render();


	int getIndexX() { return indexX; }
	int getIndexY() { return indexY; }
	int gethp() { return _hp; }
	int getMoveRange() { return moveRange; }
	int getAttack() { return attack; }
	int getAvoid() { return avoid; }
	int getCritcal() { return critcal; }
	int getSpeed() { return speed; }
	bool getPointing() { return _pointing; }
	bool getPlayerSelect() { return _playerSelect; }
	bool getAttackSelect() { return _attackSelect; }
	bool getUse() { return use; }
	int getEnemySize() { return _astar->getEnemysize(); }
	int getEnemyX(int i) { return _astar->getEnemyX(i); }
	int getEnemyY(int i) { return _astar->getEnemyY(i); }
	float getExp() { return exp; }
	

	void setLinkMap(tileSet* map) { _map = map; }
	void sethp(int hp) { _hp = hp; }
	void setExp(float Exp) { exp = Exp; }
	void setpointing(bool pointing) { _pointing = pointing; }
	void setPlayerSelect(bool Select) { _playerSelect = Select; }
	void setMoveSelect(bool Select) { _moveSelect = Select; }
	void setAttackSelect(bool Select) { _attackSelect = Select; }
	void setBattle(bool _battle) { battle = _battle; }
	void setUse(bool _use) { use = _use; }
};

