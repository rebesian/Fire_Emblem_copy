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
	int isPoint(int _ptx, int _pty);


	int getMaxEnemy() { return _vEnemy.size(); }
	int getIndexX(int pointed) { return _vEnemy[pointed]->getIndexX(); }
	int getIndexY(int pointed) { return _vEnemy[pointed]->getIndexY(); }
	bool getPlayerSelect(int pointed) { return _vEnemy[pointed]->getPlayerSelect(); }
	bool getAttackSelect(int pointed) { return _vEnemy[pointed]->getAttackSelect(); }
	bool getUse(int pointed) { return _vEnemy[pointed]->getUse(); }
	string getName(int pointed) { return _vEnemy[pointed]->getName(); }
	int gethp(int pointed) { return _vEnemy[pointed]->gethp(); }
	int getMoveRange(int pointed) { return _vEnemy[pointed]->getMoveRange(); }
	int getAttack(int pointed) { return _vEnemy[pointed]->getAttack(); }
	int getAvoid(int pointed) { return _vEnemy[pointed]->getAvoid(); }
	int getCritcal(int pointed) { return _vEnemy[pointed]->getCritcal(); }
	int getSpeed(int pointed) { return  _vEnemy[pointed]->getSpeed(); }

	void targetOn(int pointed, int idx, int idy) { _vEnemy[pointed]->targetOn(idx, idy); }
	void sethp(int pointed, int hp) { _vEnemy[pointed]->sethp(hp); }
	void setExp(int pointed, float exp) { _vEnemy[pointed]->setExp(exp); }
	void setUse(int pointed, bool use) { _vEnemy[pointed]->setUse(use); }
	void setRender(int pointed, bool render) { _vEnemy[pointed]->setrender(render); }
	void setPlayerSelect(int pointed, bool Select) { _vEnemy[pointed]->setPlayerSelect(Select); }
	void setMoveSelect(int pointed, bool Select) { _vEnemy[pointed]->setMoveSelect(Select); }
	void setAttackSelect(int pointed, bool Select) { _vEnemy[pointed]->setAttackSelect(Select); }
	void setLinkMap(tileSet* map) { _map = map; }

};

