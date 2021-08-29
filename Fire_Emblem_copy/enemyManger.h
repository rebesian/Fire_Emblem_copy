#pragma once
#include "warrior.h"
#include "socialKnight.h"
#include "soider.h"
#include "ArmorKnight.h"
#include "archer.h"
class tileSet;
class enemyManger
{
	warrior* _warrior;
	socialKnight* _social;
	soider* _soider;
	ArmorKnight* _armor;
	archer* _archer;
	tileSet* _map;

	vector<unit*> _vEnemy;
	vector<unit*>::iterator _viEnemy;

public:
	HRESULT init(TYPE type = ENEMY);
	void update(int idx, int idy);
	void release();
	void render();
	void setLinkMap(tileSet* map) { _map = map; }
};

