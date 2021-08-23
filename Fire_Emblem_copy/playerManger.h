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
	Roy* roy;
	vector<unit*> _vplayer;
public:
	HRESULT init(int idx, int idy, TYPE type = PLAYER);
	void update();
	void release();
	void render();
};

