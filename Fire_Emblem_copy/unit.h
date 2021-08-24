#pragma once
#include "gameNode.h"
#include "tileSet.h"
#include "aStarTest.h"
class unit : public gameNode
{
protected:

	tileSet* _map;
	aStarTest* _astar;
	RECT _rc;
	image* _img;
	TYPE _type;
	PLAYER_ENEMY_DIRECTION _dir;


	int indexX, indexY, endX, endY;
	int moveRange;

	int _hp;
	int attack;
	int critcal;
	int speed;
	float stageX, stageY;
	float battleX, battleY;
	float exp;
	int avoid;

	bool battle;

	int stageRenderX;
	int stageRenderY;
	bool _moving, _pointing;
	int battleRender;

	int stageRenderCount;
	int battleRenderCount;
public:
	virtual HRESULT init(int idx, int idy, TYPE type);
	virtual void update();
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
	float getExp() { return exp; }

	void setLinkMap(tileSet* map) { _map = map; }
	void sethp(int hp) { _hp = hp; }
	void setpointing(bool pointing) { _pointing = pointing; }
	void setendIndex(int endx, int endy) { endX = endx; endY = endy; }
};

