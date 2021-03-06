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
	int targetPlayerX, targetPlayerY;
	float exp;
	int avoid;

	bool use, battle;

	int stageRenderX;
	int stageRenderY;
	bool _render , _moving, _pointing, _playerSelect, _moveSelect ,_attackSelect;

	int stageRenderCount;
public:
	virtual HRESULT init(int idx, int idy, int moveRange,TYPE type);
	virtual void update(int idx, int idy);
	virtual void release();
	virtual void render();

	void targetOn(int idx, int idy);

	int getIndexX() { return indexX; }
	int getIndexY() { return indexY; }
	TYPE getType() { return _type; }
	int gethp() { return _hp; }
	int getMoveRange() { return moveRange; }
	int getAttack() { return attack; }
	int getAvoid() { return avoid; }
	int getCritcal() { return critcal; }
	int getSpeed() { return speed; }
	bool getPointing() { return _pointing; }
	bool getPlayerSelect() { return _playerSelect; }
	bool getAttackSelect() { return _attackSelect; }
	bool getBattle() { return battle; }
	bool getUse() { return use; }
	string getName() { return name; }
	int getEnemySize() { return _astar->getEnemysize(); }
	int getEnemyX(int i) { return _astar->getEnemyX(i); }
	int getEnemyY(int i) { return _astar->getEnemyY(i); }
	int getBattleX() { return targetPlayerX; }
	int getBattleY() { return targetPlayerY; }
	float getExp() { return exp; }
	

	void setLinkMap(tileSet* map) { _map = map; }
	void setMoveTile(int idx, int idy , TYPE type) { _astar->setMoveTile(idx, idy , type); }
	
	void sethp(int hp) { _hp = hp; }
	void setExp(float Exp) { exp = Exp; }
	void setrender(bool render) { _render = render; }
	void setpointing(bool pointing) { _pointing = pointing; }
	void setAstarClear() { _astar->clear(); _astar->setStart(false); _astar->EndSelect(indexX, indexY , true); }
	void setPlayerSelect(bool Select) { _playerSelect = Select; }
	void setMoveSelect(bool Select) { _moveSelect = Select; }
	void setAttackSelect(bool Select) { _attackSelect = Select; }
	void setBattle(bool _battle) { battle = _battle; }
	void setUse(bool _use) { use = _use; }
};

