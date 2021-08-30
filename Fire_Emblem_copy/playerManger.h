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
	bool getPlayerSelect(int pointed) { return _vplayer[pointed]->getPlayerSelect(); }
	bool getAttackSelect(int pointed) { return _vplayer[pointed]->getAttackSelect(); }

	void setPlayerSelect(int pointed, bool Select) { _vplayer[pointed]->setPlayerSelect(Select); }
	void setMoveSelect(int pointed, bool Select) { _vplayer[pointed]->setMoveSelect(Select); }
	void setAttackSelect(int pointed , bool Select) { _vplayer[pointed]->setAttackSelect(Select); }
	void setLinkMap(tileSet* map) { _map = map; }
};

