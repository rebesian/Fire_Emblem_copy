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

	vector<unit*> _vplayer;
public:
	HRESULT init(TYPE type = PLAYER);
	void update();
	void release();
	void render();
};

