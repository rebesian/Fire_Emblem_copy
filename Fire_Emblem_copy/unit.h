#pragma once
#include "gameNode.h"
#include "tileSet.h"

class unit : public gameNode
{
protected:

	tileSet* _map;

	image* _img;
	TYPE type;
	int indexX, indexY;
	int moveRange;
	int attack;
	int avoid;
	int critcal;
	int speed;
	float stageX, stageY;
	float battleX, battleY;
	float exp;

	int stageRenderX;
	int stageRenderY;

	int battleRender;

	int stageRenderCount;
	int battleRenderCount;
public:
	virtual HRESULT init(int idx, int idy);
	virtual void update();
	virtual void release();
	virtual void render();


	int getIndexX() { return indexX; }
	int getIndexY() { return indexY; }
	int getMoveRange() { return moveRange; }
	int getAttack() { return attack; }
	int getAvoid() { return avoid; }
	int getCritcal() { return critcal; }
	int getSpeed() { return speed; }
	float getExp() { return exp; }

	void setLinkMap(tileSet* map) { _map = map; }

};

