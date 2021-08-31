#pragma once
#include "Roy.h"
#include "warrior.h"
#include "Swordsman.h"
#include "paladin.h"
#include "archer.h"
#include "ArmorKnight.h"
#include "mage.h"
#include "mercenary.h"
#include "Pegasus.h"
#include "socialKnight.h"
#include "transport.h"

class tileSet;
class playerManger
{
	Roy* _roy;
	mage* _mage;
	warrior* _warrior;
	paladin* _paladin;
	archer* _archer;
	ArmorKnight* _armor;
	Pegasus* _Pegasus;
	socialKnight* _social;
	transport* _transport;
	Swordsman* _sword;
	 
	tileSet* _map;

	vector<unit*> _vplayer;
	vector<unit*>::iterator _viplayer;
public:
	HRESULT init(TYPE type = PLAYER);
	void update(int idx , int idy);
	void release();
	void render();

	int isPoint(int _ptx, int _pty );
	int getMaxPlayer() { return _vplayer.size(); }
	int getIndexX(int pointed) { return _vplayer[pointed]->getIndexX(); }
	int getIndexY(int pointed) { return _vplayer[pointed]->getIndexY(); }
	bool getPlayerSelect(int pointed) { return _vplayer[pointed]->getPlayerSelect(); }
	bool getAttackSelect(int pointed) { return _vplayer[pointed]->getAttackSelect(); }
	bool getUse(int pointed) { return _vplayer[pointed]->getUse(); }
	string getName(int pointed) { return _vplayer[pointed]->getName(); }
	int gethp(int pointed) { return _vplayer[pointed]->gethp(); }
	int getMoveRange(int pointed) { return _vplayer[pointed]->getMoveRange(); }
	int getAttack(int pointed) { return _vplayer[pointed]->getAttack();}
	int getAvoid(int pointed) { return _vplayer[pointed]->getAvoid();}
	int getCritcal(int pointed) { return _vplayer[pointed]->getCritcal(); }
	int getSpeed(int pointed) { return  _vplayer[pointed]->getSpeed();}



	void setMoveTile(int pointed, int idx, int idy) { _vplayer[pointed]->setMoveTile(idx, idy); }
	void sethp(int pointed , int hp) { _vplayer[pointed]->sethp(hp); }
	void setExp(int pointed, float exp) { _vplayer[pointed]->setExp(exp); }
	void setUse(int pointed, bool use) { _vplayer[pointed]->setUse(use); }
	void setPlayerSelect(int pointed, bool Select) { _vplayer[pointed]->setPlayerSelect(Select); }
	void setMoveSelect(int pointed, bool Select) { _vplayer[pointed]->setMoveSelect(Select); }
	void setAttackSelect(int pointed , bool Select) { _vplayer[pointed]->setAttackSelect(Select); }
	void setLinkMap(tileSet* map) { _map = map; }
};

